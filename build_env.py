import os
import json

def parse_env_file(filepath=".env"):
    """Membaca berkas .env sederhana tanpa ketergantungan library pihak ketiga."""
    config = {}
    if os.path.exists(filepath):
        with open(filepath, "r", encoding="utf-8") as f:
            for line in f:
                line = line.strip()
                if not line or line.startswith("#"):
                    continue
                if "=" in line:
                    key, val = line.split("=", 1)
                    key = key.strip()
                    val = val.strip().strip('"').strip("'")
                    config[key] = val
    return config

def build():
    """Menghasilkan config.js dari .env lokal dan environment variables sistem (Netlify / CI-CD)."""
    # 1. Baca nilai dari .env lokal
    config = parse_env_file(".env")

    # 2. Periksa apakah ada environment variables sistem (misal saat build di Netlify / GitHub Actions)
    keys = ["SUPABASE_URL", "SUPABASE_ANON_KEY", "DEFAULT_APP_MODE", "ESP32_IP"]
    for key in keys:
        env_val = os.getenv(key)
        if env_val:
            config[key] = env_val

    # 3. Format objek window.__ENV__
    env_payload = {
        "SUPABASE_URL": config.get("SUPABASE_URL", ""),
        "SUPABASE_ANON_KEY": config.get("SUPABASE_ANON_KEY", ""),
        "DEFAULT_APP_MODE": config.get("DEFAULT_APP_MODE", "supabase"),
        "ESP32_IP": config.get("ESP32_IP", "")
    }

    js_content = f"""// =========================================================================
// SMART HOME ESP32 - RUNTIME ENVIRONMENT CONFIGURATION
// Berkas ini di-generate secara otomatis oleh build_env.py.
// Jangan mengedit berkas ini langsung; ubah .env atau Netlify Env Vars.
// =========================================================================
window.__ENV__ = {json.dumps(env_payload, indent=4)};
"""

    with open("config.js", "w", encoding="utf-8") as f:
        f.write(js_content)

    print(f"config.js generated successfully! (Supabase URL: '{env_payload['SUPABASE_URL'][:30]}...')")
    return env_payload

if __name__ == "__main__":
    build()
