{
  "targets": [
    {
      "target_name": "slib",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "sources": [ "src\\slib.cc", "src\\internal.cc" ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")",
        "src\\include"
      ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
    }
  ]
}
