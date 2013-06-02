#include "Camera.h"
#include "Mouse.h"
#include "MouseState.h"
#include "MathHelper.h"

using namespace kXNA;
Camera::Camera(GameWin* pGame, XMVECTOR vecCameraPosition, XMVECTOR vecCameraTarget, XMVECTOR vecCameraUp)
    : GameComponent(pGame)
{
    m_vecCameraPosition = vecCameraPosition;
    m_vecCameraDirection = vecCameraTarget - vecCameraPosition;
    m_vecCameraUp = vecCameraUp;
    CreateLookToViewMatrix();
    CreatePerspectiveFieldOfViewProjectionMatrix();
}

Camera::~Camera(void)
{
}

void Camera::CreateLookToViewMatrix()
{
    XMMATRIX matView = XMMatrixLookToLH( m_vecCameraPosition, m_vecCameraDirection, m_vecCameraUp );
    SetView(matView);
}

void Camera::CreatePerspectiveFieldOfViewProjectionMatrix(FLOAT fFieldOfView
    , FLOAT fNearPlaneDistance
    , FLOAT fFarPlaneDistance)
{
    RECT rc;
    GetClientRect( GetGame()->GetWindow(), &rc );
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;
    m_matProjection = XMMatrixPerspectiveFovLH( fFieldOfView, width / (FLOAT)height, fNearPlaneDistance, fFarPlaneDistance );
}

void Camera::Initialize()
{
    GameComponent::Initialize();

    HWND hWnd = GetGame()->GetWindow();
    RECT rectClient;
    GetClientRect(hWnd, &rectClient);
    Mouse::GetInstance()->SetPosition((rectClient.right - rectClient.left)/2
        , (rectClient.bottom - rectClient.top)/2 );
}

void Camera::Update(GameTime gameTime)
{
    GameComponent::Update(gameTime);

    FLOAT yawAngle = (-MathHelper::PiOver4 / 150) * (Mouse::GetInstance()->GetState()).GetX();
    //if (fabs(currentYaw + yawAngle) < totalYaw)
    //{
    //    m_vecCameraDirection = m_vecCameraDirection * XMMATRIX.
    //}
}