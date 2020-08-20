#include "Color.h"

void HSVtoRGB(int h, int s, int v, int& r, int& g, int& b) {
    h %= MAX_H;
    s = min(MAX_SV, s);
    v = min(MAX_SV, v);
    float _h = (float)h, _s = (float)s, _v = (float)v;
    const float _max = _v;
    const float _min = _max - ((_s / MAX_SV) * _max);

    _s /= (float)MAX_SV;
    _v /= (float)MAX_SV;

    if (s == 0) {
        r = (int)(_v * 255.f);
        g = (int)(_v * 255.f);
        b = (int)(_v * 255.f);
        return;
    }

    float _r = 0, _g = 0, _b = 0;
    int dh = (int)(_h / 60.f);
    float p = _v * (1.f - _s);
    float q = _v * (1.f - _s * (_h / 60.f - dh));
    float t = _v * (1.f - _s * (1 - (_h / 60.f - dh)));

    switch (dh) {
    case 0: _r = _v; _g =  t; _b =  p; break;
    case 1: _r =  q; _g = _v; _b =  p; break;
    case 2: _r =  p; _g = _v; _b =  t; break;
    case 3: _r =  p; _g =  q; _b = _v; break;
    case 4: _r =  t; _g =  p; _b = _v; break;
    case 5: _r = _v; _g =  p; _b =  q; break;
    }

    r = (int)(_r * 255.f);
    g = (int)(_g * 255.f);
    b = (int)(_b * 255.f);
}

void RGBtoHSV(int r, int g, int b, int& h, int& s, int& v) {

    const float _max = (float)max((max(r, g)), b);
    const float _min = (float)min((min(r, g)), b);
    v = (int)(_max / 255.f * MAX_SV);

    if (_max == _min) {
        h = 0;
        s = 0;
    }
    else {
             if (_max == r) h = (int)(60.f * (float)(g - b) / (_max - _min)        );
        else if (_max == g) h = (int)(60.f * (float)(b - r) / (_max - _min) + 120.f);
        else if (_max == b) h = (int)(60.f * (float)(r - g) / (_max - _min) + 240.f);
        
             if (h > 360) h -= 360;
        else if (h <   0) h += 360;
        s = (int)((_max - _min) / _max * MAX_SV);
    }
}

unsigned int GetColorHSV(int h, int s, int v) {
    int r, g, b;
    HSVtoRGB(h, s, v, r, g, b);
    return DxLib::GetColor(r, g, b);
}