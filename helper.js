function getString (ptr) {
    const view = new Uint8Array(wasmMemory.buffer, ptr);
    let string = '';
    let i = 0;
    while (view[i] !== 0) {
        string += String.fromCharCode(view[i++]);
        if(i > 50) {
            console.error("[getString] probably encountered an error.");
            return string;
        }
    }
    return string;
}