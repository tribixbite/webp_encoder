//
// Copyright (c) 2023 xiaozhuai
//

#pragma once

#include <cstdint>
#include <string>

struct WebpFileOptions {
    /**
     * If true, minimize the output size (slow). Implicitly
     * disables key-frame insertion.
     */
    bool minimize = true;

    /**
     * loop count (default: 0, = infinite loop)
     */
    int loop = 0;

    /**
     * Minimum and maximum distance between consecutive key
     * frames in the output. The library may insert some key
     * frames as needed to satisfy this criteria.
     * Note that these conditions should hold: kmax > kmin
     * and kmin >= kmax / 2 + 1. Also, if kmax <= 0, then
     * key-frame insertion is disabled; and if kmax == 1,
     * then all frames will be key-frames (kmin value does
     * not matter for these special cases).
     */
    int kmax = 0;
    int kmin = 0;

    /**
     * If true, use mixed compression mode; may choose
     */
    bool mixed = true;

    [[nodiscard]] std::string to_string() const;
};

struct WebpFrameOptions {
    /**
     * timestamp of this frame in milliseconds.
     */
    int duration = 100;

    /**
     * Lossless encoding
     */
    bool lossless = false;

    /**
     * between 0 and 100. For lossy, 0 gives the smallest
     * size and 100 the largest. For lossless, this
     * parameter is the amount of effort put into the
     * compression: 0 is the fastest but gives larger
     * files compared to the slowest, but best, 100.
     */
    float quality = 100.0f;

    /**
     * quality/speed trade-off (0=fast, 6=slower-better)
     */
    int method = 0;

    /**
     * if true, preserve the exact RGB values under
     * transparent area. Otherwise, discard this invisible
     * RGB information for better compression.
     */
    bool exact = false;

    // --- Extended libwebp config fields ---

    /** Spatial Noise Shaping strength (0-100). Higher = more aggressive SNS. */
    int sns_strength = 50;

    /** Deblocking filter strength (0-100). */
    int filter_strength = 60;

    /** Filter sharpness (0-7). Higher = less filtering. */
    int filter_sharpness = 0;

    /** Filter type: 0=simple, 1=strong (default). */
    int filter_type = 1;

    /** Auto-adjust filter strength (0 or 1). */
    int autofilter = 0;

    /** Transparency-compression quality (0-100). */
    int alpha_quality = 100;

    /** Algorithm for encoding alpha plane (0=none, 1=lossless). */
    int alpha_compression = 1;

    /** Predictive filtering method for alpha (0=none, 1=fast, 2=best). */
    int alpha_filtering = 1;

    /** Number of entropy-analysis passes (1-10). More = smaller file, slower. */
    int pass = 1;

    /** Preprocessing filter (0=none, 1=segment-smooth, 2=pseudo-random dithering). */
    int preprocessing = 0;

    /** Near-lossless quality (0-100, 100=off). Trades minimal visual loss for smaller lossless files. */
    int near_lossless = 100;

    /** Use sharp (and target) YUV conversion (0 or 1). Better chroma on sharp edges. */
    int sharp_yuv = 0;

    /** Target output size in bytes (0=off). Overrides quality if set. */
    int target_size = 0;

    /** Max number of segments (1-4). */
    int segments = 4;

    /** Partition size limit (0=off). Quality degradation allowed to fit partition limit. */
    int partition_limit = 0;

    /** Reduce memory usage at cost of CPU (0 or 1). */
    int low_memory = 0;

    /** Map internal quality metric to JPEG quality scale (0 or 1). */
    int emulate_jpeg_size = 0;

    [[nodiscard]] std::string to_string() const;
};

class WebpEncoder {
public:
    WebpEncoder() = default;

    ~WebpEncoder();

    /**
     * Init encoder
     *
     * @param options       Webp file options
     * @return
     */
    bool Init(const WebpFileOptions &options);

    /**
     * Release all internal resources
     */
    void Release();

    /**
     * push a webp frame
     *
     * @param pixels        Pixels data in RGBA format
     * @param width         Frame width
     * @param height        Frame height
     * @param options       Frame options
     * @return
     */
    bool Push(uint8_t *pixels, int width, int height, const WebpFrameOptions &options);

    /**
     * Return webp bytes
     *
     * @param size          Bytes length
     * @return              Webp bytes
     */
    const uint8_t *Encode(size_t *size);

    /**
     * Write a webp file
     *
     * @param file          File path
     */
    void Write(const std::string &file);

private:
    int width_ = -1;
    int height_ = -1;
    int loop_ = 0;
    int timestamp_ms_ = 0;
    void *raw_handler_ = nullptr;
};
