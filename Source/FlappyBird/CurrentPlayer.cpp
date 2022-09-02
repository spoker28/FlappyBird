// Fill out your copyright notice in the Description page of Project Settings.


#include "CurrentPlayer.h"

ACurrentPlayer::ACurrentPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	Score = 0;

	IsAlive = true;
	IsPlayerStarted = false;
	
	GetCapsuleComponent()->SetCapsuleRadius(25.0f, true);
	GetCapsuleComponent()->SetCapsuleHalfHeight(25.0f, true);

	GetArrowComponent()->SetupAttachment(GetCapsuleComponent());

	ConstructorHelpers::FObjectFinder<USoundCue> JumpAudio(TEXT("SoundCue'/Game/Audio/Cues/Jump_Cue.Jump_Cue'"));
	if (JumpAudio.Succeeded())
	{
		JumpSoundCue = JumpAudio.Object;

		JumpAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("SoundAudioComponent"));
		JumpAudioComponent->SetupAttachment(GetCapsuleComponent());
	}

	GetSprite()->SetupAttachment(GetCapsuleComponent());
	GetSprite()->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	GetSprite()->SetRelativeScale3D(FVector(2.5f, 2.5f, 2.5f));
	ConstructorHelpers::FObjectFinder<UPaperFlipbook> FlipbookAssetObj(TEXT("PaperFlipbook'/Game/Flipbooks/Player_Flipbook.Player_Flipbook'"));
	GetSprite()->SetFlipbook(FlipbookAssetObj.Object);

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACurrentPlayer::OnOverlapBegin);

}

// Called when the game starts or when spawned
void ACurrentPlayer::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->GravityScale = 0.0f;
	if (JumpAudioComponent && JumpSoundCue) {
		
		JumpAudioComponent->SetSound(JumpSoundCue);
	}

}

// Called every frame
void ACurrentPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACurrentPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACurrentPlayer::Jump);
}

void ACurrentPlayer::Jump()
{
	if (IsAlive) {
		if (!IsPlayerStarted)
		{
			IsPlayerStarted = true;
			GetCharacterMovement()->GravityScale = 1.0f;
			
		}

		JumpAudioComponent->Play();

		LaunchCharacter(FVector(0.0f, 0.0f, 350.0f), false, true);

		GetSprite()->SetFlipbook(Cast<UPaperFlipbook>(StaticLoadObject(UPaperFlipbook::StaticClass(), nullptr, TEXT("PaperFlipbook'/Game/Flipbooks/PlayerJump_Flipbook.PlayerJump_Flipbook'"))));
	    GetWorldTimerManager().SetTimer(Timer, [&]()
		{
				GetSprite()->SetFlipbook(Cast<UPaperFlipbook>(StaticLoadObject(UPaperFlipbook::StaticClass(), nullptr, TEXT("PaperFlipbook'/Game/Flipbooks/Player_Flipbook.Player_Flipbook'"))));
		}, 0.5f, false);
	} else
	{
		FName Level = FName(TEXT("World'/Game/StarterContent/Maps/Minimal_Default.Minimal_Default'"));
		UGameplayStatics::OpenLevel(this, Level);
	}
}

void ACurrentPlayer::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherComp->ComponentHasTag(FName("Death"))) {
		if (IsAlive) {
			LaunchCharacter(FVector(0.0f, 0.0f, 350.0f), false, true);
			USoundBase* DeathSound = Cast<USoundCue>(StaticLoadObject(USoundCue::StaticClass(), nullptr, TEXT("SoundCue'/Game/Audio/Cues/Death_Cue.Death_Cue'")));
			UGameplayStatics::PlaySound2D(this, DeathSound);
		}
		IsAlive = false;
		GetWorldTimerManager().SetTimer(Timer, this, &ACurrentPlayer::RotatePlayerAfterDeath, 0.1f, true, 0.0f);
	} else if (OtherComp->ComponentHasTag(FName("Score up"))) {
		UpdateScore();
	}
}



void ACurrentPlayer::RotatePlayerAfterDeath()
{
	FRotator NewRotator = GetSprite()->GetRelativeRotation();
	NewRotator.Add(-50.0f, 0.0f, 0.0f);
	GetSprite()->SetRelativeRotation(NewRotator);
}

int ACurrentPlayer::GetScore()
{
	return Score;
}

void ACurrentPlayer::UpdateScore()
{
	Score += 1;
}


FText ACurrentPlayer::GetScoreIntText()
{
	FString ScoreString = "Score: " + FString::FromInt(Score);
	FText ScoreText = FText::FromString(ScoreString);
	return ScoreText;
}

