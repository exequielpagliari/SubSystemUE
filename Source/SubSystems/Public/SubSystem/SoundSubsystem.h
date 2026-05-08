// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SoundSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class SUBSYSTEMS_API USoundSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Sound | Get")
	inline float GetMasterVolume() const { return MasterVolume; }
	UFUNCTION(BlueprintCallable, Category = "Sound | Get")
	inline float GetMusicVolume() const { return MusicVolume; }
	UFUNCTION(BlueprintCallable, Category = "Sound | Get")
	inline float GetSFXVolume() const { return SFXVolume; }
	UFUNCTION(BlueprintCallable, Category = "Sound | Set")
	inline void SetMasterVolume(float NewVolume) { MasterVolume = FMath::Clamp(NewVolume, 0.f, 1.f); }
	UFUNCTION(BlueprintCallable, Category = "Sound | Set")
	inline void SetMusicVolume(float NewVolume) { MusicVolume = FMath::Clamp(NewVolume, 0.f, 1.f); }
	UFUNCTION(BlueprintCallable, Category = "Sound | Set")
	inline void SetSFXVolume(float NewVolume) { SFXVolume = FMath::Clamp(NewVolume, 0.f, 1.f); }
private:
	float MasterVolume = 1.f;
	float MusicVolume = 1.f;
	float SFXVolume = 1.f;
};
