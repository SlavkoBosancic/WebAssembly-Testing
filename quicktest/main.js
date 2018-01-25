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

window.internalFunctions = {};

var Module = {
  preRun: [function(){
    window.internalFunctions.moveBall = Module.cwrap('MoveBall', null)
  }],
  postRun: [function(){
    var interval = setInterval(function(){
      window.internalFunctions.moveBall();
    }, 20);
  }]
};

// var Module = {
//   noInitialRun: false,     // should main() be called automaticly (Default: false)
//   monitorRunDependencies: function(leftDependencies) { /* number of dependencies left to load, before init */ },
//   preRun: [function(){ /* called before initializing main() */ }],
//   onRuntimeInitialized: function(){ /* called after initialization, just before starting main() */ },
//   postRun: [function(){ /* called after main() finished */ }]
// };
