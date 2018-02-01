var canvasElemenet = document.getElementById("pong");
var canvasWidth = canvasElemenet.width;
var canvasHeight = canvasElemenet.height;
var canvasContext = canvasElemenet.getContext("2d");


window.cppFunctions = {};     // Fuctions to be called from JS -> C++

window.jsFunctions = {        // Functions to be called from C++ -> JS
  jsClearCanvas: function () {
    canvasContext.clearRect(0, 0, canvasWidth, canvasHeight);
  },
  jsDrawRectangle: function (x, y, width, height) {
    canvasContext.beginPath();
    canvasContext.fillStyle = "Gold";

    canvasContext.rect(x, y, width, height);
    canvasContext.fill();
  },
  jsDrawCircle: function (x, y, radius) {
    canvasContext.beginPath();
    canvasContext.fillStyle = "Red";

    canvasContext.arc(x + radius, y + radius, radius, 0*Math.PI, 2*Math.PI);
    canvasContext.fill();
  }
};

var startGame = function(){
  // Start moving the ball
  var interval = setInterval(function(){
    cppFunctions.moveBall();
  }, 20);

  // Start listening for KEY DOWN on document level
  // Player one: [q - 81] [a - 65]
  // Player two: [ArrowUp - 38] [ArrowDown - 40]
  document.addEventListener("keydown", function(event){

    switch(event.keyCode){
      case 81:
        // Player one: UP [q - 81]
        cppFunctions.movePaddle(true, false);
        break;
      case 65:
        // Player one: DOWN [a - 65]
        cppFunctions.movePaddle(true, true);
        break;
      case 38:
        // Player two: UP [ArrowUp - 38]
        cppFunctions.movePaddle(false, false);
        break;
      case 40:
        // Player two: DOWN [ArrowDown - 40]
        cppFunctions.movePaddle(false, true);
        break;

    }
  });
}

var Module = {
  preRun: [function(){
    cppFunctions.moveBall = Module.cwrap('MoveBall', null);                             // void MoveBall()
    cppFunctions.movePaddle = Module.cwrap('MovePaddle', null, ['number', 'number']);   // void MovePaddle(bool leftPaddle, bool moveDOWN)
  }],
  postRun: [function(){
    startGame();
  }]
};

// var Module = {
//   noInitialRun: false,     // should main() be called automaticly (Default: false)
//   monitorRunDependencies: function(leftDependencies) { /* number of dependencies left to load, before init */ },
//   preRun: [function(){ /* called before initializing main() */ }],
//   onRuntimeInitialized: function(){ /* called after initialization, just before starting main() */ },
//   postRun: [function(){ /* called after main() finished */ }]
// };