#include "Bindable.h"

ID3D11DeviceContext* Bindable::GetContext(Graphics& gfx) noexcept
{
    return nullptr;
}

ID3D11Device* Bindable::GetDevice(Graphics& gfx) noexcept
{
    return nullptr;
}

DxgiInfoManager& Bindable::GetInfoManager(Graphics& gfx) noexcept(NDEBUG)
{
    static DxgiInfoManager dummy;  // ��̬��������������������ֻ��ʼ��һ��
    return dummy;
}
