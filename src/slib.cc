#include <napi.h>
#include "internal.hpp"

Napi::String chInSc(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  auto tonic = info[0].ToString().Utf8Value();
  auto mode = info[1].ToString().Utf8Value();
  std::string o;
  int t = 0;

  

  return Napi::String::New(env, tonic+mode + std::to_string(nnn(tonic)));
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "chordsInScale"),
              Napi::Function::New(env, chInSc));
  return exports;
}

NODE_API_MODULE(slib, Init)
