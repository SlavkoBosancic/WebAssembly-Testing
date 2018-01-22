(function() {

  var canvasElemenet = document.getElementById("pong");
  var canvasWidth = canvasElemenet.width;
  var canvasHeight = canvasElemenet.height;
  var canvasContext = canvasElemenet.getContext("2d");

  var importObject = {
    imports: {},
    env: {},
    global: {}
  };

  window.externalFunctions = {
    jsClearCanvas: function () {
      debugger;
      canvasContext.clearRect(0, 0, canvasWidth, canvasHeight);
    },
    jsDrawRectangle: function (x, y, width, height) {
      debugger;
      canvasContext.fillStyle = "yellow";
      canvasContext.fillRect(x, y, width, height);
    },
    jsDrawCircle: function (x, y, width, height) {
      debugger;
      canvasContext.clearRect(x, y, w, h);
    }
  };

  fetch('pong.wasm').then(response => {
    debugger;
    return response.arrayBuffer();
  }).then(bytes =>{
    debugger;
    return WebAssembly.compile(bytes)
  }).then(module => {
    debugger;
    var t = new WebAssembly.Instance(module);
  });

})();