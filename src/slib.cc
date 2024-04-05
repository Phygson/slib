#include "napi.h"
#include "internal.hpp"

Napi::String chInSc(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  auto tonic = info[0].ToString().Utf8Value();
  auto mode = info[1].ToString().Utf8Value();
  std::string o;
  Note t { tonic };
  Note s { mode };

  

  return Napi::String::New(env, std::to_string(t.interval(s)));
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "chordsInScale"),
              Napi::Function::New(env, chInSc));
  return exports;
}

NODE_API_MODULE(slib, Init)
