tb = require("./index");

tb.init();
tb.setClearAttributes(tb.TB_DEFAULT, tb.TB_DEFAULT);
tb.clear();
tb.present();
for (var i=0; i<tb.height(); i++) {
	tb.changeCell(i, i, String.fromCharCode(i + 33), tb.TB_MAGENTA, tb.TB_DEFAULT);
	tb.present();
}
setTimeout(function() {
	tb.shutdown();
}, 2500)

