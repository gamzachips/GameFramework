#include "pch.h"
#include "Util.h"

HRESULT Util::LoadBitmapFromFile(ID2D1RenderTarget* rt, IWICImagingFactory* wic, const wchar_t* filename, OUT ID2D1Bitmap** outBitmap)
{
    ComPtr<IWICBitmapDecoder> decoder;

    HR(wic->CreateDecoderFromFilename(
        filename, nullptr, GENERIC_READ,
        WICDecodeMetadataCacheOnDemand, &decoder));

    ComPtr<IWICBitmapFrameDecode> frame;
    HR(decoder->GetFrame(0, &frame));

    ComPtr<IWICFormatConverter> converter;
    HR(wic->CreateFormatConverter(&converter));
    HR(converter->Initialize(
        frame.Get(),
        GUID_WICPixelFormat32bppPBGRA,
        WICBitmapDitherTypeNone, nullptr, 0.f,
        WICBitmapPaletteTypeCustom));


    return rt->CreateBitmapFromWicBitmap(converter.Get(),nullptr, outBitmap);
}
