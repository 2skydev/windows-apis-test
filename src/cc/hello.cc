#include <napi.h>
#include <windows.h>

int key()
{
  // This structure will be used to create the keyboard
  // input event.
  INPUT ip;

  // Set up a generic keyboard event.
  ip.type = INPUT_KEYBOARD;
  ip.ki.wScan = 0; // hardware scan code for key
  ip.ki.time = 0;
  ip.ki.dwExtraInfo = 0;

  // Press the "A" key
  ip.ki.wVk = 0x41;  // virtual-key code for the "a" key
  ip.ki.dwFlags = 0; // 0 for key press
  SendInput(1, &ip, sizeof(INPUT));

  // Release the "A" key
  ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
  SendInput(1, &ip, sizeof(INPUT));

  // Exit normally
  return 0;
}

Napi::Number Key(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  return Napi::Number::New(env, key());
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set("add", Napi::Function::New(env, Key));
  return exports;
}

NODE_API_MODULE(hello, Init)