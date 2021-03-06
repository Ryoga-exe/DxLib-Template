﻿#pragma once
#include "DxLib.h"
#define MAX_H  (360)
#define MAX_SV (100)

void         HSVtoRGB   (int h, int s, int v, int& r, int& g, int& b);
void         RGBtoHSV   (int r, int g, int b, int& h, int& s, int& v);
unsigned int GetColorHSV(int h, int s, int v);

struct Color {
    Color() : m_r(0), m_g(0), m_b(0), m_h(0), m_s(0), m_v(0), m_color(0U){
    }
    Color(int r, int g, int b) {
        Set(r, g, b);
    }
    Color(int h, int s, int v, bool isHSV) {
        SetHSV(h, s, v);
    }
    Color(unsigned int color) {
        m_color = color;
        DxLib::GetColor2(color, &m_r, &m_g, &m_b);
        RGBtoHSV(m_r, m_g, m_b, m_h, m_s, m_v);
    }
    Color& operator =(const unsigned int& q) {
        m_color = q;
        DxLib::GetColor2(q, &m_r, &m_g, &m_b);
        RGBtoHSV(m_r, m_g, m_b, m_h, m_s, m_v);
        return *this;
    }
    void Set(int r, int g, int b) {
        m_r = r, m_g = g, m_b = b;
        RGBtoHSV(r, g, b, m_h, m_s, m_v);
        m_color = DxLib::GetColor(r, g, b);
    }
    void SetHSV(int h, int s, int v) {
        m_h = h, m_s = s, m_v = v;
        HSVtoRGB(h, s, v, m_r, m_g, m_b);
        m_color = DxLib::GetColor(m_r, m_g, m_b);
    }

    unsigned int Get() { return m_color; }
    void GetRGB(int& r, int& g, int& b) { r = m_r; g = m_g; b = m_b; }
    void GetHSV(int& h, int& s, int& v) { h = m_h; s = m_s; v = m_v; }
    int GetR() { return m_r; }
    int GetG() { return m_g; }
    int GetB() { return m_b; }
    int GetH() { return m_h; }
    int GetS() { return m_s; }
    int GetV() { return m_v; }
    
    COLOR_U8 GetU8(int a) {
        return DxLib::GetColorU8(m_r, m_g, m_b, a);
    }

private:
    int m_r, m_g, m_b;
    int m_h, m_s, m_v;

    unsigned int m_color;
};

struct ColorU8 {
    ColorU8() {
        m_color = DxLib::GetColorU8(0, 0, 0, 0);
    }
    ColorU8(int r, int g, int b, int a) {
        m_color = DxLib::GetColorU8(r, g, b, a);
    }
    ColorU8(COLOR_U8 color) {
        m_color = color;
    }
    ColorU8& operator =(const COLOR_U8& q) {
        m_color = q;
        return *this;
    }
    /*ColorU8 &operator =(Color &q) {
        ColorU8(q.GetR(), q.GetG(), q.GetB(), 255);
        return *this;
    }*/
    COLOR_U8 Get() { return m_color; }
private:
    COLOR_U8 m_color;
};

typedef struct {
    Color col1, col2, col3, col4;
}ColorRect_t;