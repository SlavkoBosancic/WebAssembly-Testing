var canvasElemenet = document.getElementById("pong");
var canvasWidth = canvasElemenet.width;
var canvasHeight = canvasElemenet.height;
var canvasContext = canvasElemenet.getContext("2d");

window.externalFunctions = {
  jsClearCanvas: function () {
    canvasContext.clearRect(0, 0, canvasWidth, canvasHeight);
  },
  jsDrawRectangle: function (x, y, width, height) {
    canvasContext.beginPath();
    canvasContext.fillStyle = "yellow";

    canvasContext.rect(x, y, width, height);
    canvasContext.fill();
  },
  jsDrawCircle: function (x, y, radius) {
    canvasContext.beginPath();
    canvasContext.fillStyle = "red";

    canvasContext.arc(x + radius, y + radius, radius, 0*Math.PI, 2*Math.PI);
    canvasContext.fill();
  }
};

canvasElemenet.addEventListener("click", function(event, data){
  debugger;
  document.cMoveBall = Module.cwrap('MoveBall', null);
});

  // fetch('pong.wasm').then(response => {
  //   debugger;
  //   return response.arrayBuffer();
  // }).then(bytes =>{
  //   debugger;
  //   return WebAssembly.compile(bytes)
  // }).then(module => {
  //   debugger;
  //   var t = new WebAssembly.Instance(module);
  // });
