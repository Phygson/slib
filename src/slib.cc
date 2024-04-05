#include "napi.h"
#include "internal.hpp"

Napi::String ntInSc(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  auto tonic = info[0].ToString().Utf8Value();
  auto mode = info[1].ToString().Utf8Value();

  Note t { tonic };
  auto qq = notesInScale(t, mode);

  std::string o;
  for (auto& a : qq) o += a.get() + " ";

  return Napi::String::New(env, o);
}

Napi::String chInSc(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  auto tonic = info[0].ToString().Utf8Value();
  auto mode = info[1].ToString().Utf8Value();

  Note t { tonic };
  auto qq = notesInScale(t, mode);
  qq.push_back(qq[0]);
  qq.push_back(qq[1]);
  qq.push_back(qq[2]);
  qq.push_back(qq[3]);

  std::string o = "";
  for (int i = 0; i < 7; i++) {
    o += qq[i].get();
    if (qq[i].interval(qq[i+4]) == 6) { o += "dim"; o += " "; continue; }
    if (qq[i].interval(qq[i+2])==3) o += "m";
    o += " ";
  };

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
