-- =========================================================================
-- SMART HOME ESP32 - SUPABASE POSTGRESQL DATABASE SCHEMA
-- =========================================================================
-- Eksekusi skrip ini di SQL Editor pada Dashboard Supabase Anda:
-- https://app.supabase.com/project/_/sql
-- =========================================================================

-- 1. Tabel Ruangan (rooms)
CREATE TABLE IF NOT EXISTS public.rooms (
    id TEXT PRIMARY KEY,
    name TEXT NOT NULL,
    icon TEXT DEFAULT 'fa-lightbulb',
    is_custom BOOLEAN DEFAULT false,
    display_order INT DEFAULT 0,
    created_at TIMESTAMPTZ DEFAULT NOW()
);

-- 2. Tabel Perangkat Hardware (devices)
CREATE TABLE IF NOT EXISTS public.devices (
    id TEXT PRIMARY KEY,
    room_id TEXT REFERENCES public.rooms(id) ON DELETE CASCADE,
    name TEXT NOT NULL,
    gpio INT NOT NULL UNIQUE,
    state INT DEFAULT 0, -- 0: OFF, 1: ON
    icon TEXT DEFAULT 'fa-lightbulb',
    type TEXT DEFAULT 'light',
    last_updated TIMESTAMPTZ DEFAULT NOW()
);

-- 3. Tabel Riwayat Aktivitas (activity_logs)
CREATE TABLE IF NOT EXISTS public.activity_logs (
    id UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    timestamp TIMESTAMPTZ DEFAULT NOW(),
    device_id TEXT,
    device_name TEXT,
    room_name TEXT,
    action TEXT,
    state INT,
    triggered_by TEXT DEFAULT 'Web User'
);

-- 4. Tabel Pengaturan Sistem (settings)
CREATE TABLE IF NOT EXISTS public.settings (
    key TEXT PRIMARY KEY,
    value TEXT NOT NULL,
    updated_at TIMESTAMPTZ DEFAULT NOW()
);

-- 5. Data Awal (Starter Seed Data)
INSERT INTO public.rooms (id, name, icon, is_custom, display_order)
VALUES
    ('kamar-utama', 'Kamar Utama', 'fa-bed', false, 1),
    ('ruang-tamu', 'Ruang Tamu', 'fa-couch', false, 2),
    ('dapur-modern', 'Dapur Modern', 'fa-utensils', false, 3),
    ('kamar-mandi', 'Kamar Mandi', 'fa-bath', false, 4),
    ('alarm-rumah', 'Alarm Rumah', 'fa-bell', false, 5)
ON CONFLICT (id) DO NOTHING;

INSERT INTO public.devices (id, room_id, name, gpio, state, icon, type)
VALUES
    ('dev_red', 'ruang-tamu', 'Lampu Utama (Port 1)', 2, 0, 'fa-lightbulb', 'light'),
    ('dev_green', 'kamar-utama', 'Lampu Utama (Port 2)', 4, 0, 'fa-bed', 'light'),
    ('dev_blue', 'kamar-mandi', 'Lampu Utama (Port 3)', 5, 0, 'fa-tint', 'light'),
    ('dev_purple', 'kamar-utama', 'Lampu Tidur (Port 4)', 12, 0, 'fa-moon', 'light'),
    ('dev_white', 'kamar-utama', 'AC Kamar (Port 5)', 13, 0, 'fa-snowflake', 'ac'),
    ('dev_yellow', 'dapur-modern', 'Lampu Utama (Port 10)', 18, 0, 'fa-utensils', 'light'),
    ('dev_orange', 'alarm-rumah', 'Sirene Alarm (Port 11)', 19, 0, 'fa-bell', 'alarm')
ON CONFLICT (id) DO NOTHING;

INSERT INTO public.settings (key, value)
VALUES
    ('esp32_ip', ''),
    ('ac_temp', '24'),
    ('admin_name', 'Admin Smart Home'),
    ('admin_pin', '8888'),
    ('family_pin', '1234')
ON CONFLICT (key) DO NOTHING;

-- 6. Aktifkan Realtime Replication untuk Tabel devices dan activity_logs
-- Memungkinkan WebSocket realtime sinkronisasi ke seluruh klien dan smartphone
ALTER PUBLICATION supabase_realtime ADD TABLE public.devices;
ALTER PUBLICATION supabase_realtime ADD TABLE public.activity_logs;

-- 7. Atur Keamanan Row Level Security (RLS)
ALTER TABLE public.rooms ENABLE ROW LEVEL SECURITY;
ALTER TABLE public.devices ENABLE ROW LEVEL SECURITY;
ALTER TABLE public.activity_logs ENABLE ROW LEVEL SECURITY;
ALTER TABLE public.settings ENABLE ROW LEVEL SECURITY;

-- Kebijakan Akses Publik (Anon Key)
DROP POLICY IF EXISTS "Allow public read-write for rooms" ON public.rooms;
CREATE POLICY "Allow public read-write for rooms" ON public.rooms FOR ALL USING (true) WITH CHECK (true);

DROP POLICY IF EXISTS "Allow public read-write for devices" ON public.devices;
CREATE POLICY "Allow public read-write for devices" ON public.devices FOR ALL USING (true) WITH CHECK (true);

DROP POLICY IF EXISTS "Allow public read-write for activity_logs" ON public.activity_logs;
CREATE POLICY "Allow public read-write for activity_logs" ON public.activity_logs FOR ALL USING (true) WITH CHECK (true);

DROP POLICY IF EXISTS "Allow public read-write for settings" ON public.settings;
CREATE POLICY "Allow public read-write for settings" ON public.settings FOR ALL USING (true) WITH CHECK (true);
