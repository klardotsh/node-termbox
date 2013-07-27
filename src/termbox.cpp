/* termbox.cpp - termbox bindings for node
 *
 *  Copyright (c) 2013 Josh Klar <j@iv597.com>
 *
 *  Do whatever you want with this code as long as you leave this header.
 *  This code has no warranty. If shit hits the fan, it's your problem.
 */

#include <stdlib.h>
#include <v8.h>
#include <node.h>
#include <node_object_wrap.h>
#include <termbox.h>

using namespace v8;
using namespace node;

Handle<Value> TB_Init(const Arguments &args) {
	HandleScope scope;
	int ret = tb_init();
	if (ret < 0) {
		return ThrowException(String::New("Initialization Failed"));
	} else {
		return scope.Close(Number::New(ret));
	}
}

Handle<Value> TB_Shutdown(const Arguments &args) {
	HandleScope scope;
	tb_shutdown();
	return scope.Close(Number::New(0));
}

Handle<Value> TB_Width(const Arguments &args) {
	HandleScope scope;
	return scope.Close(Number::New(tb_width()));
}

Handle<Value> TB_Height(const Arguments &args) {
	HandleScope scope;
	return scope.Close(Number::New(tb_height()));
}

Handle<Value> TB_Clear(const Arguments &args) {
	HandleScope scope;
	tb_clear();
	return scope.Close(Number::New(0));
}

Handle<Value> TB_Present(const Arguments &args) {
	HandleScope scope;
	tb_present();
	return scope.Close(Number::New(0));
}

Handle<Value> TB_Set_Cursor(const Arguments &args) {
	HandleScope scope;
	if (args[0]->IsNumber() && args[1]->IsNumber()) {
		tb_set_cursor(args[0]->Int32Value(), args[1]->Int32Value());
		return scope.Close(Number::New(0));
	} else {
		return ThrowException(String::New("setCursor(<Number> cx, <Number> cy)"));
	}
}

Handle<Value> TB_Hide_Cursor(const Arguments &args) {
	HandleScope scope;
	tb_set_cursor(-1, -1);
	return scope.Close(Number::New(0));
}

Handle<Value> TB_Change_Cell(const Arguments &args) {
	HandleScope scope;
	if (args[0]->IsNumber() &&
		args[1]->IsNumber() &&
		args[2]->IsString() &&
		args[3]->IsNumber() &&
		args[4]->IsNumber()) {
		String::Utf8Value arg2(args[2]);
		int res1 = *(*arg2);
		tb_change_cell(
			args[0]->Int32Value(),
			args[1]->Int32Value(),
			res1,
			args[3]->Int32Value(),
			args[4]->Int32Value()
		);
		return scope.Close(Number::New(0));
	} else {
		return ThrowException(String::New("changeCell(<Number> x, <Number> y, <Number> ch, <Number> fg, <Number> bg)"));
	}
}

Handle<Value> TB_Select_Input_Mode(const Arguments &args) {
	HandleScope scope;
	if (args[0]->IsNumber()) {
		return scope.Close(Number::New(tb_select_input_mode(args[0]->Int32Value())));
	} else {
		return ThrowException(String::New("selectInputMode(<Number> mode)"));
	}
}

Handle<Value> TB_Set_Clear_Attributes(const Arguments &args) {
	HandleScope scope;
	if (args[0]->IsNumber() && args[1]->IsNumber()) {
		tb_set_clear_attributes(args[0]->Int32Value(), args[1]->Int32Value());
		return scope.Close(Number::New(0));
	} else {
		return ThrowException(String::New("setClearAttributes(<Number> fg, <Number> bg)"));
	}
}

Handle<Value> TB_Peek_Event(const Arguments &args) {
	HandleScope scope;
	tb_event e;
	int ret;
	if (args[0]->IsNumber()) {
		ret = tb_peek_event(&e, args[0]->Int32Value());
		switch (ret) {
			case -1:
				return scope.Close(Undefined());
			case 0:
				return scope.Close(Undefined());
			default:
				Handle<Object> retObj = Object::New();
				retObj->Set(String::New("type"), Number::New(e.type));
				retObj->Set(String::New("mod"), Number::New(e.mod));
				retObj->Set(String::New("key"), Number::New(e.key));
				retObj->Set(String::New("ch"), Number::New(e.ch));
				retObj->Set(String::New("w"), Number::New(e.w));
				retObj->Set(String::New("h"), Number::New(e.h));
				return scope.Close(retObj);
		}
	} else {
		return ThrowException(String::New("peekEvent(<Number> timeout)"));
	}
}

Handle<Value> TB_Poll_Event(const Arguments &args) {
	HandleScope scope;
	tb_event e;
	int ret;
	ret = tb_poll_event(&e);
	switch (ret) {
		case -1:
			return scope.Close(Undefined());
		case 0:
			return scope.Close(Undefined());
		default:
			Handle<Object> retObj = Object::New();
			retObj->Set(String::New("type"), Number::New(e.type));
			retObj->Set(String::New("mod"), Number::New(e.mod));
			retObj->Set(String::New("key"), Number::New(e.key));
			retObj->Set(String::New("ch"), Number::New(e.ch));
			retObj->Set(String::New("w"), Number::New(e.w));
			retObj->Set(String::New("h"), Number::New(e.h));
			return scope.Close(retObj);
	}
}

void init (Handle<Object> target) {
	HandleScope scope;
	
	// FUNCTIONS
	target->Set(String::New("init"), FunctionTemplate::New(TB_Init)->GetFunction()); 
	target->Set(String::New("shutdown"), FunctionTemplate::New(TB_Shutdown)->GetFunction());
	target->Set(String::New("width"), FunctionTemplate::New(TB_Width)->GetFunction());
	target->Set(String::New("height"), FunctionTemplate::New(TB_Height)->GetFunction());
	target->Set(String::New("clear"), FunctionTemplate::New(TB_Clear)->GetFunction());
	target->Set(String::New("present"), FunctionTemplate::New(TB_Present)->GetFunction());
	target->Set(String::New("setCursor"), FunctionTemplate::New(TB_Set_Cursor)->GetFunction());
	target->Set(String::New("hideCursor"), FunctionTemplate::New(TB_Hide_Cursor)->GetFunction());
	target->Set(String::New("changeCell"), FunctionTemplate::New(TB_Change_Cell)->GetFunction());
	target->Set(String::New("selectInputMode"), FunctionTemplate::New(TB_Select_Input_Mode)->GetFunction());
	target->Set(String::New("setClearAttributes"), FunctionTemplate::New(TB_Set_Clear_Attributes)->GetFunction());
	target->Set(String::New("peekEvent"), FunctionTemplate::New(TB_Peek_Event)->GetFunction());
	target->Set(String::New("pollEvent"), FunctionTemplate::New(TB_Poll_Event)->GetFunction());

	// CONSTANTS
	target->Set(String::New("TB_KEY_F1"), Number::New(TB_KEY_F1));
	target->Set(String::New("TB_KEY_F2"), Number::New(TB_KEY_F2));
	target->Set(String::New("TB_KEY_F3"), Number::New(TB_KEY_F3));
	target->Set(String::New("TB_KEY_F4"), Number::New(TB_KEY_F4));
	target->Set(String::New("TB_KEY_F5"), Number::New(TB_KEY_F5));
	target->Set(String::New("TB_KEY_F6"), Number::New(TB_KEY_F6));
	target->Set(String::New("TB_KEY_F7"), Number::New(TB_KEY_F7));
	target->Set(String::New("TB_KEY_F8"), Number::New(TB_KEY_F8));
	target->Set(String::New("TB_KEY_F9"), Number::New(TB_KEY_F9));
	target->Set(String::New("TB_KEY_F10"), Number::New(TB_KEY_F10));
	target->Set(String::New("TB_KEY_F11"), Number::New(TB_KEY_F11));
	target->Set(String::New("TB_KEY_F12"), Number::New(TB_KEY_F12));
	target->Set(String::New("TB_KEY_INSERT"), Number::New(TB_KEY_INSERT));
	target->Set(String::New("TB_KEY_DELETE"), Number::New(TB_KEY_DELETE));
	target->Set(String::New("TB_KEY_HOME"), Number::New(TB_KEY_HOME));
	target->Set(String::New("TB_KEY_END"), Number::New(TB_KEY_END));
	target->Set(String::New("TB_KEY_PGUP"), Number::New(TB_KEY_PGUP));
	target->Set(String::New("TB_KEY_PGDN"), Number::New(TB_KEY_PGDN));
	target->Set(String::New("TB_KEY_ARROW_UP"), Number::New(TB_KEY_ARROW_UP));
	target->Set(String::New("TB_KEY_ARROW_DOWN"), Number::New(TB_KEY_ARROW_DOWN));
	target->Set(String::New("TB_KEY_ARROW_LEFT"), Number::New(TB_KEY_ARROW_LEFT));
	target->Set(String::New("TB_KEY_ARROW_RIGHT"), Number::New(TB_KEY_ARROW_RIGHT));
	target->Set(String::New("TB_KEY_CTRL_TILDE"), Number::New(TB_KEY_CTRL_TILDE));
	target->Set(String::New("TB_KEY_CTRL_2"), Number::New(TB_KEY_CTRL_TILDE));
	target->Set(String::New("TB_KEY_CTRL_A"), Number::New(TB_KEY_CTRL_A));
	target->Set(String::New("TB_KEY_CTRL_B"), Number::New(TB_KEY_CTRL_B));
	target->Set(String::New("TB_KEY_CTRL_C"), Number::New(TB_KEY_CTRL_C));
	target->Set(String::New("TB_KEY_CTRL_D"), Number::New(TB_KEY_CTRL_D));
	target->Set(String::New("TB_KEY_CTRL_E"), Number::New(TB_KEY_CTRL_E));
	target->Set(String::New("TB_KEY_CTRL_F"), Number::New(TB_KEY_CTRL_F));
	target->Set(String::New("TB_KEY_CTRL_G"), Number::New(TB_KEY_CTRL_G));
	target->Set(String::New("TB_KEY_BACKSPACE"), Number::New(TB_KEY_BACKSPACE));
	target->Set(String::New("TB_KEY_CTRL_H"), Number::New(TB_KEY_CTRL_H));
	target->Set(String::New("TB_KEY_TAB"), Number::New(TB_KEY_TAB));
	target->Set(String::New("TB_KEY_CTRL_I"), Number::New(TB_KEY_CTRL_I));
	target->Set(String::New("TB_KEY_CTRL_J"), Number::New(TB_KEY_CTRL_J));
	target->Set(String::New("TB_KEY_CTRL_K"), Number::New(TB_KEY_CTRL_K));
	target->Set(String::New("TB_KEY_CTRL_L"), Number::New(TB_KEY_CTRL_L));
	target->Set(String::New("TB_KEY_ENTER"), Number::New(TB_KEY_ENTER));
	target->Set(String::New("TB_KEY_CTRL_M"), Number::New(TB_KEY_CTRL_M));
	target->Set(String::New("TB_KEY_CTRL_N"), Number::New(TB_KEY_CTRL_N));
	target->Set(String::New("TB_KEY_CTRL_O"), Number::New(TB_KEY_CTRL_O));
	target->Set(String::New("TB_KEY_CTRL_P"), Number::New(TB_KEY_CTRL_P));
	target->Set(String::New("TB_KEY_CTRL_Q"), Number::New(TB_KEY_CTRL_Q));
	target->Set(String::New("TB_KEY_CTRL_R"), Number::New(TB_KEY_CTRL_R));
	target->Set(String::New("TB_KEY_CTRL_S"), Number::New(TB_KEY_CTRL_S));
	target->Set(String::New("TB_KEY_CTRL_T"), Number::New(TB_KEY_CTRL_T));
	target->Set(String::New("TB_KEY_CTRL_U"), Number::New(TB_KEY_CTRL_U));
	target->Set(String::New("TB_KEY_CTRL_V"), Number::New(TB_KEY_CTRL_V));
	target->Set(String::New("TB_KEY_CTRL_W"), Number::New(TB_KEY_CTRL_W));
	target->Set(String::New("TB_KEY_CTRL_X"), Number::New(TB_KEY_CTRL_X));
	target->Set(String::New("TB_KEY_CTRL_Y"), Number::New(TB_KEY_CTRL_Y));
	target->Set(String::New("TB_KEY_CTRL_Z"), Number::New(TB_KEY_CTRL_Z));
	target->Set(String::New("TB_KEY_ESC"), Number::New(TB_KEY_ESC));
	target->Set(String::New("TB_KEY_CTRL_LSQ_BRACKET"), Number::New(TB_KEY_CTRL_LSQ_BRACKET));
	target->Set(String::New("TB_KEY_CTRL_3"), Number::New(TB_KEY_CTRL_3));
	target->Set(String::New("TB_KEY_CTRL_4"), Number::New(TB_KEY_CTRL_4));
	target->Set(String::New("TB_KEY_CTRL_BACKSLASH"), Number::New(TB_KEY_CTRL_BACKSLASH));
	target->Set(String::New("TB_KEY_CTRL_5"), Number::New(TB_KEY_CTRL_5));
	target->Set(String::New("TB_KEY_CTRL_RSQ_BRACKET"), Number::New(TB_KEY_CTRL_RSQ_BRACKET));
	target->Set(String::New("TB_KEY_CTRL_6"), Number::New(TB_KEY_CTRL_6));
	target->Set(String::New("TB_KEY_CTRL_7"), Number::New(TB_KEY_CTRL_7));
	target->Set(String::New("TB_KEY_CTRL_SLASH"), Number::New(TB_KEY_CTRL_SLASH));
	target->Set(String::New("TB_KEY_CTRL_UNDERSCORE"), Number::New(TB_KEY_CTRL_UNDERSCORE));
	target->Set(String::New("TB_KEY_SPACE"), Number::New(TB_KEY_SPACE));
	target->Set(String::New("TB_KEY_BACKSPACE2"), Number::New(TB_KEY_BACKSPACE2));
	target->Set(String::New("TB_KEY_CTRL_8"), Number::New(TB_KEY_CTRL_8));
	target->Set(String::New("TB_MOD_ALT"), Number::New(TB_MOD_ALT));
	target->Set(String::New("TB_BLACK"), Number::New(TB_BLACK));
	target->Set(String::New("TB_RED"), Number::New(TB_RED));
	target->Set(String::New("TB_GREEN"), Number::New(TB_GREEN));
	target->Set(String::New("TB_YELLOW"), Number::New(TB_YELLOW));
	target->Set(String::New("TB_BLUE"), Number::New(TB_BLUE));
	target->Set(String::New("TB_MAGENTA"), Number::New(TB_MAGENTA));
	target->Set(String::New("TB_CYAN"), Number::New(TB_CYAN));
	target->Set(String::New("TB_WHITE"), Number::New(TB_WHITE));
	target->Set(String::New("TB_DEFAULT"), Number::New(TB_DEFAULT));
	target->Set(String::New("TB_BOLD"), Number::New(TB_BOLD));
	target->Set(String::New("TB_UNDERLINE"), Number::New(TB_UNDERLINE));
	target->Set(String::New("TB_EUNSUPPORTED_TERMINAL"), Number::New(TB_EUNSUPPORTED_TERMINAL));
	target->Set(String::New("TB_EFAILED_TO_OPEN_TTY"), Number::New(TB_EFAILED_TO_OPEN_TTY));
	target->Set(String::New("TB_EPIPE_TRAP_ERROR"), Number::New(TB_EPIPE_TRAP_ERROR));
	target->Set(String::New("TB_HIDE_CURSOR"), Number::New(TB_HIDE_CURSOR));
	target->Set(String::New("TB_INPUT_ESC"), Number::New(TB_INPUT_ESC));
	target->Set(String::New("TB_INPUT_ALT"), Number::New(TB_INPUT_ALT));
	target->Set(String::New("TB_EVENT_KEY"), Number::New(TB_EVENT_KEY));
	target->Set(String::New("TB_EVENT_RESIZE"), Number::New(TB_EVENT_RESIZE));
	target->Set(String::New("TB_EOF"), Number::New(TB_EOF));

	// YAY DONE!
}

NODE_MODULE(termbox, init)
