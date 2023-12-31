#include "ActorExample.h"
#include <vector>

std::vector<std::unique_ptr<Actor>> bugs;

HRESULT ActorExample::Initialize(HINSTANCE hInstance, LPCWSTR title, UINT width, UINT height)
{
    HRESULT hr;

    hr = D2DFramework::Initialize(hInstance, title, width, height);
    ThrowIfFailed(hr);

    mspBackground = std::make_unique<Actor>(this, L"Images/back1.png", 0, 0, 1.0f);

    for (int i = 0; i < 20; i++)
    {
        bugs.push_back(mspBug = std::make_unique<Actor>(this, L"Images/bug1.png", 0.0f + i * 20.0f, 100.0f));
    }

    return S_OK;
}

void ActorExample::Release()
{
    bugs.clear();
    mspBug.reset();
    mspBackground.reset();

    D2DFramework::Release();

}

void ActorExample::Render()
{
    mspRenderTarget->BeginDraw();
    mspRenderTarget->Clear(D2D1::ColorF(0.0f, 0.2f, 0.4f, 1.0f));

    mspBackground->Draw();
   // mspBug->Draw();

    for (auto& bug: bugs)
    {
        bug->Draw();
    }

    HRESULT hr = mspRenderTarget->EndDraw();

    if (hr == D2DERR_RECREATE_TARGET)
    {
        CreateDeviceResources();
    }

}