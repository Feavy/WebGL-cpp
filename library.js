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
            images[counter].onload = function() {
                this.onload = undefined;
                this.onerror = undefined;
                out("Image loaded successfully");
                wakeUp(counter);
            };
            images[counter].onerror = function() {
                this.onload = undefined;
                this.onerror = undefined;
                out("Error loading image " + path);
                wakeUp(0);
            };
            images[counter].src = path;
        });
    },
    flip_image_vertically: function(imageIndex) {
        return Asyncify.handleSleep(wakeUp => {
            var img = images[imageIndex];
            if (!img) {
                wakeUp();
            }
            var canvas = document.createElement('canvas');
            canvas.width = img.width;
            canvas.height = img.height;
            var ctx = canvas.getContext('2d');
            ctx.scale(1, -1);
            ctx.drawImage(img, 0, -img.height);
            img.src = canvas.toDataURL();
            img.onload = function() {
                this.onload = undefined;
                this.onerror = undefined;
                wakeUp();
            };
        });
    },
    glTexImage2D_external: function(target, level, internalFormat, format, type, imageIndex) {
        if (images[imageIndex]) {
            GLctx.texImage2D(target, level, internalFormat, format, type, images[imageIndex]);
        } else {
            console.warn("WebGL: No image for index", imageIndex);
        }
    }
});