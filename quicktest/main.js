var ctx = document.getElementById("pong")
                  .getContext("2d");

var env = {
  setInterval: function (x) {
    setInterval(() => {
      wasmInstance.exports.runCallback(x);  
    }, 16);
  },
  jsFillRect: function (x, y, w, h) {
    ctx.fillStyle = "orange";
    ctx.fillRect(x, y, w, h);
  },
  jsClearRect: function (x, y, w, h) {
    ctx.clearRect(x, y, w, h);
  }
}

var wasmModule = new WebAssembly.Module(wasmCode);
var wasmInstance = new WebAssembly.Instance(wasmModule, {
  env: env
});
var m = new Uint8Array(wasmInstance.exports.memory.buffer);

lib.setStackPtr(wasmInstance.exports.memory, 0x2000);

wasmInstance.exports.main();

lib.showCanvas(true);