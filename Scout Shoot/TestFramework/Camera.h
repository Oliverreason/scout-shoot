#pragma once
#include "stdApp.h"

#include "GameComponent.h"
#include "Color.h"
#include "GameWin.h"
#include "GameTime.h"

using namespace kXNA;


class Camera : 
    public GameComponent
{
public:
    Camera(GameWin* pGame, XMVECTOR vecCameraPosition, XMVECTOR vecCameraTarget, XMVECTOR vecCameraUp);
    virtual ~Camera(void);

    inline XMMATRIX GetView() const { return m_matView; }
    inline XMMATRIX GetProjection() const { return m_matProjection; }
    inline XMVECTOR GetCameraPosition() const { return m_vecCameraPosition; }

    virtual void Initialize();
    virtual void Update(GameTime gameTime);

protected:
    inline void SetView(const XMMATRIX& matView) { m_matView = matView; }
    inline void SetProjection(const XMMATRIX& matProjection) { m_matProjection = matProjection; }
    inline void SetCameraPosition(const XMVECTOR& vecCameraPosition) { m_vecCameraPosition = vecCameraPosition; }

private:
    void CreateLookToViewMatrix();
    void CreatePerspectiveFieldOfViewProjectionMatrix(FLOAT fFieldOfView = XM_PIDIV2
        , FLOAT fNearPlaneDistance = 0.01f
        , FLOAT fFarPlaneDistance = 100.0f);

    XMMATRIX m_matView;
    XMMATRIX m_matProjection;
    XMVECTOR m_vecCameraPosition;

    XMVECTOR m_vecCameraDirection;
    XMVECTOR m_vecCameraUp;
    FLOAT currentPitch;
    FLOAT currentYaw;
    //MouseState prevMouseState;
    FLOAT totalPitch;
    FLOAT totalYaw;
};

