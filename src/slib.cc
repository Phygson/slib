#include "napi.h"
#include <numeric>
#include "note.hpp"
#include "scales.hpp"
#include "ffc.hpp"
#include "chshape.hpp"

// FNV-1a hash, 32-bit 
inline constexpr std::uint32_t fnv1a(const char* str, std::uint32_t hash = 2166136261UL) {
    return *str ? fnv1a(str + 1, (hash ^ *str) * 16777619ULL) : hash;
}

Napi::String ntInSc(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  auto tonic = info[0].ToString().Utf8Value();
  auto mode = info[1].ToString().Utf8Value();

  Note t { tonic };
  auto qq = notesInScale(t, mode);

  std::string o;
  for (auto& a : qq) o += a.get() + " ";
  o.pop_back();
  o += "\n";
  switch (fnv1a(mode.data())) {
        case fnv1a("Lyd"): o += "1 2 3 #4 5 6 7";  break;
        case fnv1a("Ion"): o += "1 2 3 4 5 6 7"; break;
        case fnv1a("Mixolyd"): o +=  "1 2 3 4 5 6 b7";  break;
        case fnv1a("Dor"): o += "1 2 b3 4 5 6 b7"; break;
        case fnv1a("Aeo"): o += "1 2 b3 4 5 b6 b7";  break;
        case fnv1a("Phy"): o += "1 b2 b3 4 5 b6 b7"; break;
        case fnv1a("Loc"): o += "1 b2 b3 4 b5 b6 b7";  break;
    }

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

Napi::String chshape(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  return Napi::String::New(env, getChordShape(info[0].ToString().Utf8Value()));
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "notesInScale"),
              Napi::Function::New(env, ntInSc));
  exports.Set(Napi::String::New(env, "chordsInScale"),
              Napi::Function::New(env, chInSc));
  exports.Set(Napi::String::New(env, "getRomanScale"),
              Napi::Function::New(env, grs));
  exports.Set(Napi::String::New(env, "getChordShape"),
              Napi::Function::New(env, chshape));
  return exports;
}

NODE_API_MODULE(slib, Init)
