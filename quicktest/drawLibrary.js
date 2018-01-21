mergeInto(LibraryManager.library, {
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
  });