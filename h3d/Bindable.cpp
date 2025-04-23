#include "Bindable.h"

ID3D11DeviceContext* Bindable::GetContext(Graphics& gfx) noexcept
{
    return nullptr;
}

ID3D11Device* Bindable::GetDevice(Graphics& gfx) noexcept
{
    return nullptr;
}

DxgiInfoManager& Bindable::GetInfoManager(Graphics& gfx) noexcept(!_DEBUG)
{
    static DxgiInfoManager dummy;  // 静态变量，程序生命周期内只初始化一次
    return dummy;
}
