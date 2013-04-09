$(document).ready(function() {
  $("#notice").css('display', 'none');
  if ($("#notice span")) {
    $("#notice span").each(function(idx, el) {
      var span = $(el);
      $.ambiance({message: span.html(), timeout: 5, type: span.attr("class")});
    });
  }
});
