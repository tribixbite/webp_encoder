//
// Copyright (c) 2023 xiaozhuai
//

#include <emscripten/bind.h>
#include <emscripten/emscripten.h>
#include <emscripten/val.h>

#include "webp_encoder.hpp"

int main() { return 0; }

static bool WebpEncoder_Init(WebpEncoder &self, const emscripten::val &options) {
    WebpFileOptions o;
    if (options.hasOwnProperty("minimize")) {
        o.minimize = options["minimize"].as<bool>();
    }
    if (options.hasOwnProperty("loop")) {
        o.loop = options["loop"].as<int>();
    }
    if (options.hasOwnProperty("kmax")) {
        o.kmax = options["kmax"].as<int>();
    }
    if (options.hasOwnProperty("kmin")) {
        o.kmin = options["kmin"].as<int>();
    }
    if (options.hasOwnProperty("mixed")) {
        o.mixed = options["mixed"].as<bool>();
    }
    return self.Init(o);
}

static inline void WebpEncoder_Release(WebpEncoder &self) { self.Release(); }

static bool WebpEncoder_Push(WebpEncoder &self, const emscripten::val &pixels, int width, int height,
                             const emscripten::val &options) {
    auto size = pixels["length"].as<size_t>();
    std::vector<uint8_t> native_pixels(size);
    emscripten::val memoryView{emscripten::typed_memory_view(native_pixels.size(), native_pixels.data())};
    memoryView.call<void>("set", pixels);

    WebpFrameOptions o;
    if (options.hasOwnProperty("duration")) {
        o.duration = options["duration"].as<int>();
    }
    if (options.hasOwnProperty("lossless")) {
        o.lossless = options["lossless"].as<bool>();
    }
    if (options.hasOwnProperty("quality")) {
        o.quality = options["quality"].as<float>();
    }
    if (options.hasOwnProperty("method")) {
        o.method = options["method"].as<int>();
    }
    if (options.hasOwnProperty("exact")) {
        o.exact = options["exact"].as<bool>();
    }
    if (options.hasOwnProperty("sns_strength")) {
        o.sns_strength = options["sns_strength"].as<int>();
    }
    if (options.hasOwnProperty("filter_strength")) {
        o.filter_strength = options["filter_strength"].as<int>();
    }
    if (options.hasOwnProperty("filter_sharpness")) {
        o.filter_sharpness = options["filter_sharpness"].as<int>();
    }
    if (options.hasOwnProperty("filter_type")) {
        o.filter_type = options["filter_type"].as<int>();
    }
    if (options.hasOwnProperty("autofilter")) {
        o.autofilter = options["autofilter"].as<int>();
    }
    if (options.hasOwnProperty("alpha_quality")) {
        o.alpha_quality = options["alpha_quality"].as<int>();
    }
    if (options.hasOwnProperty("alpha_compression")) {
        o.alpha_compression = options["alpha_compression"].as<int>();
    }
    if (options.hasOwnProperty("alpha_filtering")) {
        o.alpha_filtering = options["alpha_filtering"].as<int>();
    }
    if (options.hasOwnProperty("pass")) {
        o.pass = options["pass"].as<int>();
    }
    if (options.hasOwnProperty("preprocessing")) {
        o.preprocessing = options["preprocessing"].as<int>();
    }
    if (options.hasOwnProperty("near_lossless")) {
        o.near_lossless = options["near_lossless"].as<int>();
    }
    if (options.hasOwnProperty("sharp_yuv")) {
        o.sharp_yuv = options["sharp_yuv"].as<int>();
    }
    if (options.hasOwnProperty("target_size")) {
        o.target_size = options["target_size"].as<int>();
    }
    if (options.hasOwnProperty("segments")) {
        o.segments = options["segments"].as<int>();
    }
    if (options.hasOwnProperty("partition_limit")) {
        o.partition_limit = options["partition_limit"].as<int>();
    }
    if (options.hasOwnProperty("low_memory")) {
        o.low_memory = options["low_memory"].as<int>();
    }
    if (options.hasOwnProperty("emulate_jpeg_size")) {
        o.emulate_jpeg_size = options["emulate_jpeg_size"].as<int>();
    }
    auto ret = self.Push(native_pixels.data(), width, height, o);
    emscripten_sleep(0);
    return ret;
}

static emscripten::val WebpEncoder_Encode(WebpEncoder &self) {
    size_t size;
    const uint8_t *data = self.Encode(&size);
    return emscripten::val(emscripten::typed_memory_view(size, data));
}

EMSCRIPTEN_BINDINGS(WebpEncoder) {
    emscripten::class_<WebpEncoder>("WebpEncoder")
        .constructor()
        .function("init", &WebpEncoder_Init)
        .function("release", &WebpEncoder_Release)
        .function("push", &WebpEncoder_Push)
        .function("encode", &WebpEncoder_Encode);
}
