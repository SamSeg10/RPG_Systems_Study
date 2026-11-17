


#include "BaseCharacters.h"
#include "AbilitySystemComponent.h"
#include "RPG_Systems_Study/GameplayAbilitySystem/Attributes/BasicAttributeSet.h"


// Sets default values
ABaseCharacters::ABaseCharacters()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	BasicAttributeSet = CreateDefaultSubobject<UBasicAttributeSet>(FName("BasicAttributeSet"));
}

// Called when the game starts or when spawned
void ABaseCharacters::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseCharacters::PossessedBy(AController* EventController)
{
	Super::PossessedBy(EventController);
	
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

// Called every frame
void ABaseCharacters::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABaseCharacters::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UAbilitySystemComponent* ABaseCharacters::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

