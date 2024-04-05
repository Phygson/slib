#include "napi.h"
#include "internal.hpp"

Napi::String ntInSc(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  auto tonic = info[0].ToString().Utf8Value();
  auto mode = info[1].ToString().Utf8Value();

  Note t { tonic };
  auto qq = notesInScale(t, mode);

  std::string o;
  for (auto& a : qq) o += a.get();

  return Napi::String::New(env, o);
}

Napi::String chInSc(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  auto tonic = info[0].ToString().Utf8Value();
  auto mode = info[1].ToString().Utf8Value();

  Note t { tonic };
  auto qq = notesInScale(t, mode);

  std::string o;
  for (auto& a : qq) o += a.get();

  return Napi::String::New(env, o);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "notesInScale"),
              Napi::Function::New(env, ntInSc));
  exports.Set(Napi::String::New(env, "chordsInScale"),
              Napi::Function::New(env, chInSc));
  return exports;
}

NODE_API_MODULE(slib, Init)
