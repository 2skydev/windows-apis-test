#include <napi.h>
#include <windows.h>

void keydown()
{
  INPUT ip;

  ip.type = INPUT_KEYBOARD;
  ip.ki.wScan = 0;
  ip.ki.time = 0;
  ip.ki.dwExtraInfo = 0;
  ip.ki.wVk = 0x41;
  ip.ki.dwFlags = 0;

  SendInput(1, &ip, sizeof(INPUT));
}

void keyup()
{
  INPUT ip;

  ip.type = INPUT_KEYBOARD;
  ip.ki.wScan = 0;
  ip.ki.time = 0;
  ip.ki.dwExtraInfo = 0;
  ip.ki.wVk = 0x41;
  ip.ki.dwFlags = KEYEVENTF_KEYUP;

  SendInput(1, &ip, sizeof(INPUT));
}

Napi::Number Keydown(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  keydown();
  return Napi::Number::New(env, 1);
}

Napi::Number Keyup(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  keyup();
  return Napi::Number::New(env, 1);
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  exports.Set("keydown", Napi::Function::New(env, Keydown));
  exports.Set("keyup", Napi::Function::New(env, Keyup));

  return exports;
}

NODE_API_MODULE(input, Init)