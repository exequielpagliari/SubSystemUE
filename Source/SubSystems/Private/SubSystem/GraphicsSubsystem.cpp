// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystem/GraphicsSubsystem.h"
#include "GameFramework/GameUserSettings.h"

void UGraphicsSubsystem::SetResolution(int32 Width, int32 Height, bool bFullscreen)
{
    if (UGameUserSettings* Settings = GetSettings())
    {
        Settings->SetScreenResolution(FIntPoint(Width, Height));
        Settings->SetFullscreenMode(bFullscreen ? EWindowMode::Fullscreen : EWindowMode::Windowed);
    }
}

void UGraphicsSubsystem::GetResolution(int32& OutWidth, int32& OutHeight, bool& OutFullscreen) const
{
    if (const UGameUserSettings* Settings = GetSettings())
    {
        FIntPoint Res = Settings->GetScreenResolution();
        OutWidth = Res.X;
        OutHeight = Res.Y;
        OutFullscreen = Settings->GetFullscreenMode() == EWindowMode::Fullscreen;
    }
}

void UGraphicsSubsystem::SetScalabilityGroup(int32 QualityLevel)
{
    if (UGameUserSettings* Settings = GetSettings())
    {
        // 0 = Low, 1 = Medium, 2 = High, 3 = Epic, 4 = Cinematic
        Settings->SetOverallScalabilityLevel(QualityLevel);
    }
}

int32 UGraphicsSubsystem::GetScalabilityGroup() const
{
    if (const UGameUserSettings* Settings = GetSettings())
    {
        return Settings->GetOverallScalabilityLevel();
    }
    return 3;
}

void UGraphicsSubsystem::ApplyAndSaveSettings()
{
    if (UGameUserSettings* Settings = GetSettings())
    {
        Settings->ApplySettings(false); // Aplica y guarda en .ini
    }
}

void UGraphicsSubsystem::RunAutoBenchmark()
{
    if (UGameUserSettings* Settings = GetSettings())
    {
        Settings->RunHardwareBenchmark();
        Settings->ApplyHardwareBenchmarkResults();
        Settings->ApplySettings(false);
    }
}

UGameUserSettings* UGraphicsSubsystem::GetSettings() const
{
    return UGameUserSettings::GetGameUserSettings();
}

TArray<FIntPoint> UGraphicsSubsystem::GetAvailableScreenResolutions()
{
    TArray<FIntPoint> Resolutions;
    FScreenResolutionArray RHIResolutions;


    if (RHIGetAvailableResolutions(RHIResolutions, true))
    {
        for (const FScreenResolutionRHI& Res : RHIResolutions)
        {
            if (Res.Width >= 800 && Res.Height >= 600)
            {
                Resolutions.AddUnique(FIntPoint(Res.Width, Res.Height));
            }
        }
    }

    Resolutions.Sort([](const FIntPoint& A, const FIntPoint& B) {
        return A.X != B.X ? A.X > B.X : A.Y > B.Y;
        });

    return Resolutions;
}

FString UGraphicsSubsystem::ResolutionToString(FIntPoint Resolution)
{
    return FString::Printf(TEXT("%dx%d"), Resolution.X, Resolution.Y);
}