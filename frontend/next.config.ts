import type { NextConfig } from "next";

const nextConfig: NextConfig = {
  /* config options here */
  reactStrictMode: true,

  webpack: (config ) => {
    config.externals = [...config.externals, "canvas", "jsdom"];
    config.resolve.fallback = {
      ...config.resolve.fallback,

      "node:fs/promises": false,
      fs: false,
      path: false
    };
    return config;
  }
};

export default nextConfig;
