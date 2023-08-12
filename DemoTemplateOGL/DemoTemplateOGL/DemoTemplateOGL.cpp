// DemoTemplateOGL.cpp : Defines the entry point for the application.
//
#include "framework.h"
#include "DemoTemplateOGL.h"
#include <iostream>
#include "Utilities.h"
#include "KeyboardInput.h"
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glext.h"
#include "wglext.h"
#include "model.h"
#include "MainModel.h"

#include "GamePadRR.h"
#include "Scene.h"
#include "Scenario.h"

#define MAX_LOADSTRING 100
#define Timer1 100

HINSTANCE hInst;                                // current instance
HWND hWnd;
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HDC dc;
HGLRC rc;

GamePadRR* gamPad;                  // Manejador de gamepad
bool renderiza;                     // Variable para controlar el render

double xPos = 0, yPos = 0;
double lastX = 0, lastY = 0, xoffset = 0, yoffset = 0;
POINT g_lastMousePos;

// Callback principal de la ventana en WINAPI
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

// Funciones para activar OpenGL version > 2.0
int prepareRenderWindow(HINSTANCE hInstance, int nCmdShow);
bool SetUpPixelFormat(HDC hDC, PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB, PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB);
void centerCursor(HWND hWnd);


// Propiedades de la ventana
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;
bool newContext = false; // Bandera para identificar si OpenGL 2.0 > esta activa

// Objecto de escena y render
Scene *OGLobj;
ModelResource* Resources;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DEMOTEMPLATEOGL, szWindowClass, MAX_LOADSTRING);

    // Si no logra activar OpenGL 2 o superior termina el programa
    if (prepareRenderWindow(hInstance, nCmdShow))
        return 1;

    // game loop
    gamPad = new GamePadRR(1); // Obtenemos el primer gamepad conectado

    // Main character with it's camera
    glm::vec3 translate;
    glm::vec3 scale;
    translate = glm::vec3(0.0f, 0.0f, 3.0f);
    MainModel *model = new MainModel(hWnd, "models/Cube.obj", translate);
    model->setPosition(translate);
    glm::vec3 v(0, 0, -1);
    model->setFront(v);
    scale = glm::vec3(0.25f, 0.25f, 0.25f);	// it's a bit too big for our scene, so scale it down
    model->setScale(&scale);
    model->setTranslate(&translate);
    
    OGLobj = new Scenario(hWnd, model); // Creamos nuestra escena con esa posicion de inicio
    SetTimer(hWnd, Timer1, 1000/60, (TIMERPROC)WndProc);// Asignamos el timer con un render de 30 fps
    renderiza = false;
    MSG msg = { 0 };

    int running = 1;

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    while (running) {
        if (renderiza) {
            // render
            // ------
            bool checkCollition = false;
            if (gamPad->IsConnected()) {
                //convierto a flotante el valor analogico de tipo entero
                float grados = (float)gamPad->GetState().Gamepad.sThumbLX / 32767.0;
                //debido a que los controles se aguadean con el uso entonces ya no dan el cero
                //en el centro, por eso lo comparo con una ventana de aguadencia de mi control
                if (grados > 0.19 || grados < -0.19)
                    model->CamaraGiraY(grados * 3.0);
                float velocidad = (float)gamPad->GetState().Gamepad.sThumbLY / 32767;
                if (velocidad > 0.19 || velocidad < -0.19) {
                    if (velocidad > 0)
                    {
                        velocidad = 0.3;
                    }
                    if (velocidad < 0)
                    {
                        velocidad = -0.3;
                    }
                    model->movePosition(velocidad);
                    checkCollition = true;
                }
            }
            else {
                ShowCursor(FALSE);
                checkCollition = KeysEvents(OGLobj);
                checkCollition = MouseEvents(OGLobj, xPos, yPos, xoffset, yoffset);
            }
            if (checkCollition) { // Bandera para buscar colisiones sobre Camara/Modelo
                // Posicionamos la camara/modelo pixeles arriba de su posicion en el terreno
                model->getNextPosition().y = OGLobj->getTerreno()->Superficie(model->getNextPosition().x, model->getNextPosition().z) + 1.7;
                if (OGLobj->lookForCollition() != NULL) // Llamamos a la funcion de colision 
                    model->setNextPosition(model->getPosition());
                else
                    model->CamaraAvanza();
            }
            Scene *escena = OGLobj->Render(dc);
            if (escena != OGLobj) {
                delete OGLobj;
                OGLobj = escena;
            }
            renderiza = false;
        } else if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT){
                running = 0;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return (int) msg.wParam;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_CREATE: {
        } break;
        case WM_COMMAND: {
        } break;
        case WM_TIMER: {
            OGLobj->setAngulo(OGLobj->getAngulo() + 1.5);
            if (!renderiza)
                renderiza = true;
        } break;
        case WM_PAINT: {
        }break;
        case WM_DESTROY: {
            if (newContext) {
                ReleaseDC(hWnd, dc);
                wglDeleteContext(rc);
                PostQuitMessage(0);
            }
        } break;
        case WM_SIZE: {
            if (newContext) {
                //esta opcion del switch se ejecuta una sola vez al arrancar y si se
                //afecta el tama�o de la misma se dispara de nuevo
                int height = HIWORD(lParam),
                    width = LOWORD(lParam);
                if (height == 0)
                    width = 1;
                SCR_HEIGHT = height;
                SCR_WIDTH = width;
                glViewport(0, 0, width, height);
            }
        } break;
        case WM_KEYDOWN: {
            KEYS[wParam] = true;
        } break;
        case WM_MOUSEMOVE:
        {
            /* POINT currentPos;
             currentPos.x = LOWORD(lParam);
             currentPos.y = HIWORD(lParam);

              xoffset = static_cast<double>(currentPos.x - g_lastMousePos.x);
              yoffset = static_cast<double>(currentPos.y - g_lastMousePos.y);*/

            xoffset = GET_X_LPARAM(lParam) - SCR_WIDTH / 2.0f;
            yoffset = SCR_HEIGHT / 2.0f - GET_Y_LPARAM(lParam);

            centerCursor(hWnd);
        }
        case WM_KEYUP: {
            switch (wParam) {
            case VK_ADD:
                break;
            }
        } break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

void centerCursor(HWND hWnd)
{
    // Obtener el rect�ngulo del cliente de la ventana
    RECT rect;
    GetClientRect(hWnd, &rect);

    // Calcular la posici�n del centro de la ventana
    int centerX = (rect.right - rect.left) / 2;
    int centerY = (rect.bottom - rect.top) / 2;

    // Convertir la posici�n del centro de la ventana a coordenadas de pantalla
    POINT pt = { centerX, centerY };
    ClientToScreen(hWnd, &pt);

    // Establecer la posici�n del cursor en el centro de la ventana
    SetCursorPos(pt.x, pt.y);
}

bool SetUpPixelFormat(HDC hDC, PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB, PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB) {
    const int pixelAttribs[] = {
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
        WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
        WGL_COLOR_BITS_ARB, 32,
        WGL_DEPTH_BITS_ARB, 24,
        WGL_STENCIL_BITS_ARB, 8,
//        WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
//        WGL_SAMPLES_ARB, 4,
        WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
        WGL_ALPHA_BITS_ARB, 8,
        0 
    };
    int pixelFormatID;
    UINT numFormats;
    bool status = wglChoosePixelFormatARB(hDC, pixelAttribs, NULL, 1, &pixelFormatID, &numFormats);
    if (status == false || numFormats == 0)
        return true;
    PIXELFORMATDESCRIPTOR PFD;
    DescribePixelFormat(hDC, pixelFormatID, sizeof(PFD), &PFD);
    SetPixelFormat(hDC, pixelFormatID, &PFD);
    return false;
}

// Funciones de inicializacion para ventana compatible con OpenGL
int prepareRenderWindow(HINSTANCE hInstance, int nCmdShow) {
    PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = nullptr;
    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;
    WNDCLASSEX wc;
    ZeroMemory(&wc, sizeof(WNDCLASSEX));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = szWindowClass;
    RegisterClassEx(&wc);
    hInst = hInstance;
    HWND fakeWND = CreateWindow(
        szWindowClass, L"Fake Window",      // window class, title
        WS_CLIPSIBLINGS | WS_CLIPCHILDREN, // style
        0, 0,                       // position x, y
        1, 1,                       // width, height
        NULL, NULL,                 // parent window, menu
        hInstance, NULL);           // instance, param
    HDC fakeDC = GetDC(fakeWND);        // Device Context
    PIXELFORMATDESCRIPTOR fakePFD;
    ZeroMemory(&fakePFD, sizeof(fakePFD));
    fakePFD.nSize = sizeof(fakePFD);
    fakePFD.nVersion = 1;
    fakePFD.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    fakePFD.iPixelType = PFD_TYPE_RGBA;
    fakePFD.cColorBits = 32;
    fakePFD.cAlphaBits = 8;
    fakePFD.cDepthBits = 24;
    int fakePFDID = ChoosePixelFormat(fakeDC, &fakePFD);
    if (fakePFDID == 0) {
        MessageBox(fakeWND, L"ChoosePixelFormat() failed.", L"", 0);
        return 1;
    }
    if (SetPixelFormat(fakeDC, fakePFDID, &fakePFD) == false) {
        MessageBox(fakeWND, L"SetPixelFormat() failed.", L"", 0);
        return 1;
    }
    HGLRC fakeRC = wglCreateContext(fakeDC);    // Rendering Contex
    if (fakeRC == 0) {
        MessageBox(fakeWND, L"wglCreateContext() failed.", L"", 0);
        return 1;
    }
    if (wglMakeCurrent(fakeDC, fakeRC) == false) {
        MessageBox(fakeWND, L"wglMakeCurrent() failed.", L"", 0);
        return 1;
    }
    wglChoosePixelFormatARB = reinterpret_cast<PFNWGLCHOOSEPIXELFORMATARBPROC>(wglGetProcAddress("wglChoosePixelFormatARB"));
    if (wglChoosePixelFormatARB == nullptr) {
        MessageBox(fakeWND, L"wglGetProcAddress() failed.", L"", 0);
        return 1;
    }
    wglCreateContextAttribsARB = reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>(wglGetProcAddress("wglCreateContextAttribsARB"));
    if (wglCreateContextAttribsARB == nullptr) {
        MessageBox(fakeWND, L"wglGetProcAddress() failed.", L"", 0);
        return 1;
    }
    gladLoadGL();
    // create window
    RECT wr = { 0, 0, SCR_WIDTH, SCR_HEIGHT };
    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

    hWnd = CreateWindow(szWindowClass, szTitle,
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        100, 100,
        wr.right - wr.left, //SCR_WIDTH, 
        wr.bottom - wr.top, //SCR_HEIGHT,
        NULL, NULL, hInstance, NULL);
    if (hWnd == NULL) {
        return 1;
    }
    dc = NULL;
    dc = GetDC(hWnd);
    if (SetUpPixelFormat(dc, wglChoosePixelFormatARB, wglCreateContextAttribsARB)) {
        MessageBox(hWnd, L"wglChoosePixelFormatARB() failed.", L"", 0);
        return 1;
    }
    const int major_min = 3, minor_min = 2;
    int  contextAttribs[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, major_min,
        WGL_CONTEXT_MINOR_VERSION_ARB, minor_min,
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0
    };
    rc = NULL;
//    rc = wglCreateContext(dc);
    rc = wglCreateContextAttribsARB(dc, 0, contextAttribs);
    if (rc == NULL) {
        MessageBox(hWnd, L"wglCreateContextAttribsARB() failed.", L"", 0);
        return 1;
    }
//    wglMakeCurrent(dc, rc);
    wglDeleteContext(fakeRC);
    ReleaseDC(fakeWND, fakeDC);
    DestroyWindow(fakeWND);
    if (!wglMakeCurrent(dc, rc)) {
        MessageBox(hWnd, L"wglMakeCurrent() failed.", L"", 0);
        return 1;
    }
    gladLoadGL();
    newContext = true;
    return 0;
}
