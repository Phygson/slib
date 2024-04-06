#include "napi.h"
#include <numeric>
#include "note.hpp"
#include "scales.hpp"
#include "ffc.hpp"

Napi::String ntInSc(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  auto tonic = info[0].ToString().Utf8Value();
  auto mode = info[1].ToString().Utf8Value();

  Note t { tonic };
  auto qq = notesInScale(t, mode);

  std::string o;
  for (auto& a : qq) o += a.get() + " ";
  o.pop_back();

  return Napi::String::New(env, o);
}

Napi::String chInSc(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  auto tonic = info[0].ToString().Utf8Value();
  auto mode = info[1].ToString().Utf8Value();

  Note t { tonic };

  auto qq = chordsInScale(t, mode);

  auto os = std::accumulate(std::begin(qq), std::end(qq), std::string(),
                                [](std::string &ss, std::string &s)
                                {
                                    return ss.empty() ? s : ss + " " + s;
                                });

  return Napi::String::New(env, os);
}

Napi::String grs(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  auto tonic = info[0].ToString().Utf8Value();
  auto mode = info[1].ToString().Utf8Value();

  Note t { tonic };

  auto qq = getRomanScale(t, mode);

  auto os = std::accumulate(std::begin(qq), std::end(qq), std::string(),
                                [](std::string &ss, std::string &s)
                                {
                                    return ss.empty() ? s : ss + " " + s;
                                });

  return Napi::String::New(env, os);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "notesInScale"),
              Napi::Function::New(env, ntInSc));
  exports.Set(Napi::String::New(env, "chordsInScale"),
              Napi::Function::New(env, chInSc));
  exports.Set(Napi::String::New(env, "getRomanScale"),
              Napi::Function::New(env, grs));
  return exports;
}

NODE_API_MODULE(slib, Init)
