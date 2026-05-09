// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystem/SoundSubsystem.h"
#include "Kismet/GameplayStatics.h"



void USoundSubsystem::SetMasterVolume(float NewVolume)
{
    MasterVolume = FMath::Clamp(NewVolume, 0.f, 1.f);
    UpdateMixer(MainSoundMix, MasterClass, MasterVolume);
}

void USoundSubsystem::SetMasterVolumeLogarithmic(float LinearVolume)
{
    float LogarithmicVolume = FMath::Pow(LinearVolume, 2.0f);
	SetMasterVolume(LogarithmicVolume);
}

void USoundSubsystem::SetMusicVolume(float NewVolume)
{
    MusicVolume = FMath::Clamp(NewVolume, 0.f, 1.f);
    UpdateMixer(MainSoundMix, MusicClass, MusicVolume);
}

void USoundSubsystem::SetMusicVolumeLogarithmic(float LinearVolume)
{
    float LogarithmicVolume = FMath::Pow(LinearVolume, 2.0f);
    SetMusicVolume(LogarithmicVolume);
}

void USoundSubsystem::SetSFXVolume(float NewVolume)
{
    SFXVolume = FMath::Clamp(NewVolume, 0.f, 1.f);
}

void USoundSubsystem::SetSFXVolumeLogarithmic(float LinearVolume)
{
    float LogarithmicVolume = FMath::Pow(LinearVolume, 2.0f);
	SetSFXVolume(LogarithmicVolume);
}

void USoundSubsystem::SetMainSoundMix(USoundMix* NewSoundMix)
{
    if (NewSoundMix)
    {
        MainSoundMix = NewSoundMix;
        UGameplayStatics::PushSoundMixModifier(GetWorld(), MainSoundMix);
	}
}

void USoundSubsystem::SetMasterSoundClass(USoundClass* NewSoundClass)
{
    if (NewSoundClass)
    {
        MasterClass = NewSoundClass;
        UpdateMixer(MainSoundMix, MasterClass, MasterVolume);
	}
}



void USoundSubsystem::SetMusicSoundClass(USoundClass* NewSoundClass)
{
    if (NewSoundClass)
    {
        MusicClass = NewSoundClass;
        UpdateMixer(MainSoundMix, MusicClass, MusicVolume);
	}
}

void USoundSubsystem::SetSFXSoundClass(USoundClass* NewSoundClass)
{
    if (NewSoundClass)
    {
        SFXClass = NewSoundClass;
        UpdateMixer(MainSoundMix, SFXClass, SFXVolume);
	}
}

void USoundSubsystem::UpdateMixer(USoundMix* InSoundMix, USoundClass* InSoundClass, float NewVolume)
{
	UWorld* World = GetWorld();
    if(!World)
    {
        UE_LOG(LogTemp, Warning, TEXT("World is null in UpdateMixer"));
        return;
    }
    if(!InSoundClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("Sound Class is null in UpdateMixer"));
	}
    if(!InSoundMix)
    {
        UE_LOG(LogTemp, Warning, TEXT("Sound Mix is null in UpdateMixer"));
	}
    if (InSoundMix && InSoundClass && World)
    {
		
        // Set the override
        UGameplayStatics::SetSoundMixClassOverride(
            World,
            InSoundMix,
            InSoundClass,
            NewVolume,    // New Volume (e.g., 0.5f for 50%)
            1.0f,         // New Pitch
            0.5f,         // Fade In Time (seconds)
            true          // Apply to Children?
        );

        // Ensure the mix is active/pushed for the override to take effect
        UGameplayStatics::PushSoundMixModifier(World, InSoundMix);
        UE_LOG(LogTemp, Warning, TEXT("Updated Sound Mix '%s' for Sound Class '%s' with new volume: %f"), *InSoundMix->GetName(), *InSoundClass->GetName(), InSoundClass->Properties.Volume);
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Updated Sound Mix Function"));
}
