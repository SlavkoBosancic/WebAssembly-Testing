(function() {

  var canvasElemenet = document.getElementById("pong");
  var canvasWidth = canvasElemenet.width;
  var canvasHeight = canvasElemenet.height;
  var canvasContext = canvasElemenet.getContext("2d");


  var importObject = {
    imports: {
        imported_func: function(arg) {
          console.log(arg);
        }
      }
    };

  var env = {
    imports: {
      jsClearCanvas: function () {
        debugger;
        canvasContext.clearRect(0, 0, canvasWidth, canvasHeight);
      },
      jsDrawRectangle: function (x, y, width, height) {
        debugger;
        ctx.fillStyle = "yellow";
        ctx.fillRect(x, y, width, height);
      },
      jsDrawCircle: function (x, y, width, height) {
        debugger;
        ctx.clearRect(x, y, w, h);
      }
    }
  };

  fetch('pong.wasm').then(response => {
    debugger;
    return response.arrayBuffer();
  }).then(bytes =>{
    debugger;
    return WebAssembly.instantiate(bytes, env)
  }).then(results => {
    debugger;
  });

})();