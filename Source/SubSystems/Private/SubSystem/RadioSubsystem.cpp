// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystem/RadioSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h" 

#define PLAY_MUSIC(Music) UGameplayStatics::SpawnSound2D(GetWorld(), Music, 1.0f, 1.0f, 0.0f, nullptr, true);


void URadioSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	RadioAudioComponent = NewObject<UAudioComponent>(GetGameInstance());
	RadioAudioComponent->bAutoActivate = false;
	
	RadioAudioComponent->OnAudioFinished.AddDynamic(this, &URadioSubsystem::OnTrackFinished);
}

void URadioSubsystem::LoadPlaylist(TArray<USoundBase*> NewTracks)
{
	Playlist = NewTracks;
	CurrentTrackIndex = -1;
}

void URadioSubsystem::PlayNextTrack()
{
	UE_LOG(LogTemp, Warning, TEXT("Radio: Inicia Intruccion Reproduciendo siguiente pista..."));
	UE_LOG(LogTemp, Warning, TEXT("Radio: Cantidad de pistas es %d"), Playlist.Num());
	if (Playlist.Num() == 0) return;
	

	CurrentTrackIndex = (CurrentTrackIndex + 1) % Playlist.Num();
	if (!Playlist[CurrentTrackIndex]) {
		UE_LOG(LogTemp, Warning, TEXT("Radio: Se ha reiniciado la playlist"));
	}
	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Warning, TEXT("Radio: No se pudo obtener el mundo"));
	}



	if (Playlist[CurrentTrackIndex] && World)
	{
		RadioAudioComponent->Stop();
		RadioAudioComponent = PLAY_MUSIC(Playlist[CurrentTrackIndex])


		UE_LOG(LogTemp, Log, TEXT("Radio: Reproduciendo pista %d"), CurrentTrackIndex);
	}

}

void URadioSubsystem::OnTrackFinished()
{
	PlayNextTrack();
}

void URadioSubsystem::StopRadio()
{
	if (RadioAudioComponent->IsPlaying())
	{
		RadioAudioComponent->Stop();
	}
}

void URadioSubsystem::SetRadioVolume(float Volume)
{
	RadioAudioComponent->SetVolumeMultiplier(Volume);
}