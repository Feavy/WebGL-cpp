mergeInto(LibraryManager.library, {
    consoleLog: function(strPtr) {
        console.log(UTF8ToString(strPtr));
    }
});