mergeInto(LibraryManager.library, {
    consoleLog: function(strPtr) {
        console.log(UTF8ToString(strPtr));
    },
    load_image: function(path) {
        return Asyncify.handleSleep(wakeUp => {
            path = UTF8ToString(path);
            console.log("Load image called", path);

            var counter = ++image_counter;
    
            images[counter] = new Image();
            images[counter].src = path;
            images[counter].onload = function() {
                out("Image loaded successfully");
                wakeUp(counter);
            };
            images[counter].onerror = function() {
                out("Error loading image " + path);
                wakeUp(0);
            };
        });
    },
    glTexImage2D_internal: function(target, level, internalFormat, format, type, imageIndex) {
        if(images[imageIndex]) {
            GLctx.texImage2D(target, level, internalFormat, format, type, images[imageIndex]);
        }else{
            console.warn("WebGL: No image for index", imageIndex);
        }
    }
});