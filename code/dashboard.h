#ifndef MJPC_DASHBOARD_RENDER_H
#define MJPC_DASHBOARD_RENDER_H

#include <GLFW/glfw3.h>
#ifdef _WIN32
#pragma comment(lib, "opengl32.lib")
#endif
#include <cmath>
#include <cstdio>
#include <vector>

class DashboardRenderer {
public:
    void drawLine(float x1, float y1, float x2, float y2) {
        glVertex2f(x1, y1); glVertex2f(x2, y2);
    }

    void drawDigit(float x, float y, float s, int num) {
        float w = s * 0.5f;
        float h = s;
        glBegin(GL_LINES);
        if (num != 1 && num != 4) drawLine(x - w, y + h, x + w, y + h);
        if (num != 1 && num != 2 && num != 3 && num != 7) drawLine(x - w, y + h, x - w, y);
        if (num != 5 && num != 6) drawLine(x + w, y + h, x + w, y);
        if (num != 0 && num != 1 && num != 7) drawLine(x - w, y, x + w, y);
        if (num == 0 || num == 2 || num == 6 || num == 8) drawLine(x - w, y, x - w, y - h);
        if (num != 2) drawLine(x + w, y, x + w, y - h);
        if (num != 1 && num != 4 && num != 7) drawLine(x - w, y - h, x + w, y - h);
        glEnd();
    }

    void drawNumber(float x, float y, float size, int number) {
        glLineWidth(2.0f);
        glColor4f(0.0f, 0.0f, 0.0f, 1.0f);

        if (number == 0) { drawDigit(x, y, size, 0); return; }
        float offset = (number >= 10) ? size * 0.6f : 0.0f;
        float curr_x = x + offset;
        std::vector<int> digits;
        int temp = number;
        while (temp > 0) { digits.push_back(temp % 10); temp /= 10; }
        for (int d : digits) {
            drawDigit(curr_x, y, size, d);
            curr_x -= (size * 1.4f);
        }
    }

    void drawGlassBase(float r) {
        glBegin(GL_TRIANGLE_FAN);
        glColor4f(0.8f, 0.8f, 0.8f, 0.4f);
        glVertex2f(0, 0);
        for (int i = 0; i <= 50; i++) {
            float angle = 2.0f * 3.14159f * i / 50;
            glColor4f(0.9f, 0.9f, 0.9f, 0.5f);
            glVertex2f(r * cos(angle), r * sin(angle));
        }
        glEnd();

        glLineWidth(2.0f);
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i <= 50; i++) {
            float angle = 2.0f * 3.14159f * i / 50;
            glColor4f(0.2f, 0.2f, 0.2f, 0.6f);
            glVertex2f(r * cos(angle), r * sin(angle));
        }
        glEnd();
    }

    void drawTicksAndNumbers(float r) {
        glLineWidth(2.5f);
        glBegin(GL_LINES);
        for (int i = 0; i <= 10; i++) {
            float angle_deg = 225.0f - (i * 27.0f);
            float angle_rad = angle_deg * 3.14159f / 180.0f;
            float t = (float)i / 10.0f;
            glColor4f(0.1f, 0.1f, 0.1f, 0.8f);
            glVertex2f(r * 0.85f * cos(angle_rad), r * 0.85f * sin(angle_rad));
            glVertex2f(r * 0.98f * cos(angle_rad), r * 0.98f * sin(angle_rad));
        }
        glEnd();

        float num_r = r * 1.25f;
        float s = 5.0f;
        for (int i = 0; i <= 10; i += 2) {
            float angle_deg = 225.0f - (i * 27.0f);
            float rad = angle_deg * 3.14159f / 180.0f;
            drawNumber(num_r * cos(rad), num_r * sin(rad), s, i);
        }

        glLineWidth(1.5f);
        glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
        float ux = -3.0f, uy = -r * 0.4f;
        glBegin(GL_LINES);
        glVertex2f(ux, uy); glVertex2f(ux, uy + 4);
        glVertex2f(ux, uy + 2); glVertex2f(ux + 3, uy + 4);
        glVertex2f(ux, uy + 2); glVertex2f(ux + 3, uy);
        ux += 5;
        glVertex2f(ux, uy); glVertex2f(ux, uy + 4);
        glVertex2f(ux + 4, uy); glVertex2f(ux + 4, uy + 4);
        glVertex2f(ux, uy + 4); glVertex2f(ux + 2, uy + 2);
        glVertex2f(ux + 4, uy + 4); glVertex2f(ux + 2, uy + 2);
        glEnd();
    }

    void drawLaserPointer(float r, float angle_deg) {
        float angle_rad = angle_deg * 3.14159f / 180.0f;
        glLineWidth(3.0f);
        glBegin(GL_LINES);
        glColor4f(1.0f, 0.0f, 0.0f, 0.2f);
        glVertex2f(0, 0);
        glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
        glVertex2f(r * 0.9f * cos(angle_rad), r * 0.9f * sin(angle_rad));
        glEnd();

        glPointSize(8.0f);
        glBegin(GL_POINTS);
        glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
        glVertex2f(r * 0.9f * cos(angle_rad), r * 0.9f * sin(angle_rad));
        glEnd();
    }

    void renderFollow(float speed, float x, float y, float z) {
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        glPushMatrix();
        glTranslatef(x, y, z + 1.2f);

        float modelview[16];
        glGetFloatv(GL_MODELVIEW_MATRIX, modelview);
        for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) {
            modelview[i * 4 + j] = (i == j) ? 1.0f : 0.0f;
        }
        glLoadMatrixf(modelview);

        float scale = 0.0035f;
        glScalef(scale, scale, scale);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_LIGHTING);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        drawGlassBase(80.0f);
        glTranslatef(0.0f, 0.0f, 0.5f);
        drawTicksAndNumbers(80.0f);
        glTranslatef(0.0f, 0.0f, 0.5f);
        float angle = 225.0f - (speed * 27.0f);
        drawLaserPointer(75.0f, angle);

        glPopMatrix();
        glPopAttrib();
    }

    void renderPurplePanel(int width, int height) {
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glOrtho(0, width, 0, height, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_LIGHTING);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glBegin(GL_QUADS);
        glColor4f(1.0f, 1.0f, 1.0f, 0.3f); glVertex2f(0, 0);
        glColor4f(1.0f, 1.0f, 1.0f, 0.0f); glVertex2f(350, 0);
        glColor4f(1.0f, 1.0f, 1.0f, 0.0f); glVertex2f(350, height);
        glColor4f(1.0f, 1.0f, 1.0f, 0.3f); glVertex2f(0, height);
        glEnd();

        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopAttrib();
    }
};

#endif