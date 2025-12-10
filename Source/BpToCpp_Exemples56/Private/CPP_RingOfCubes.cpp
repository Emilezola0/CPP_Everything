// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_RingOfCubes.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
ACPP_RingOfCubes::ACPP_RingOfCubes()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// INITIALIZE
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	
	HISM_00 = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("HISM_00"));
	HISM_00->SetupAttachment(SceneRoot);

	BpName = CreateDefaultSubobject<UTextRenderComponent>(TEXT("BpName"));
	BpName->SetupAttachment(SceneRoot);

	CubeCount = CreateDefaultSubobject<UTextRenderComponent>(TEXT("CubeCount"));
	CubeCount->SetupAttachment(SceneRoot);

	// INIT VAR
	AutoRadius = false;
	ShowTextRender = true;
	Radius = 300;

}

void ACPP_RingOfCubes::OnConstruction(const FTransform& Transform)
{
	HISM_00->ClearInstances();
	int Instance;

	// SET MATERIAL IF HAVE MATERIAL And set DT VALUES
	if (Material)
	{
		HISM_00->SetMaterial(0, Material);
		HISM_00->SetNumCustomDataFloats(3);
	}

	if (SM_Stone && CubesNUM > 0)
	{
		HISM_00->SetStaticMesh(SM_Stone);

		if (AutoRadius)
		{
			// USE AUTO RADIUS
			float L_Angle = 360 / float(CubesNUM);
			Radius = GetMeshHalfSize().X * UKismetMathLibrary::DegTan((180 - L_Angle) / 2);
			int i = 0;
			FVector Location;
			for (i = 0; i < CubesNUM; i++)
			{
				// Angle = (360 / CubeNUM) * i
				Location = UKismetMathLibrary::Quat_RotateVector(FQuat(FRotator(0, L_Angle * i, 0)), FVector(Radius, 0, 0));
				Instance = HISM_00->AddInstance(FTransform(
					FRotator(UKismetMathLibrary::FindLookAtRotation(Location, FVector(0, 0, 0))),
					Location,
					FVector(1, 1, 1)
				), false);

				GenerateColor(Instance);

				HISM_00->SetCustomDataValue(Instance, 0, Color.R, false);
				HISM_00->SetCustomDataValue(Instance, 1, Color.G, false);
				HISM_00->SetCustomDataValue(Instance, 2, Color.B, false);
			}


		}
		else
		{
			// Don't use auto radius
			int i = 0;
			FVector Location;
			for (i = 0; i < CubesNUM; i++)
			{
				// Angle = (360 / CubeNUM) * i
				Location = UKismetMathLibrary::Quat_RotateVector(FQuat(FRotator(0, (360 / float(CubesNUM)) * i, 0)), FVector(Radius, 0, 0));
				Instance = HISM_00->AddInstance(FTransform(
					FRotator(UKismetMathLibrary::FindLookAtRotation(Location, FVector(0, 0, 0))),
					Location,
					FVector(1, 1, 1)
				));

				GenerateColor(Instance);

				HISM_00->SetCustomDataValue(Instance, 0, Color.R, false);
				HISM_00->SetCustomDataValue(Instance, 1, Color.G, false);
				HISM_00->SetCustomDataValue(Instance, 2, Color.B, false);
			}

		}

		// IF AUTO RADIUS END

		// Rotate RingOfCubes
		HISM_00->SetRelativeRotation(Rotation);

		// --- TEXTs ---

		// VISIBILITY
		BpName->SetVisibility(ShowTextRender);
		CubeCount->SetVisibility(ShowTextRender);

		// POSITION
		BpName->SetRelativeLocation(FVector(0, 0, 25));
		CubeCount->SetRelativeLocation(FVector(0, 0, -25));

		BpName->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
		BpName->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
		CubeCount->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
		CubeCount->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);

		// IN TEXT
		BpName->SetText(FText::FromString("Ring Of Cubes"));

		FString CubeAmountText = "Cube Count : ";
		CubeAmountText.AppendInt(HISM_00->GetInstanceCount());
		CubeCount->SetText(FText::FromString(CubeAmountText));

	}
}

// Called when the game starts or when spawned
void ACPP_RingOfCubes::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_RingOfCubes::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ACPP_RingOfCubes::GetMeshHalfSize()
{
	return SM_Stone->GetBounds().GetBox().GetExtent();
}

void ACPP_RingOfCubes::GenerateColor(int NumInstance)
{
	// GENERATE COLOR DEPENDING OF ERANDOM COLOR CHOOSED
	switch (ColorGenerationType)
	{

	case ERandomColor::RndSeeded:
		Color = FLinearColor(UKismetMathLibrary::RandomFloatInRangeFromStream(0, 1, Seed), UKismetMathLibrary::RandomFloatInRangeFromStream(0, 1, Seed), UKismetMathLibrary::RandomFloatInRangeFromStream(0, 1, Seed));
		break;

	case ERandomColor::Random:
		Color = FLinearColor(UKismetMathLibrary::RandomFloatInRange(0, 1), UKismetMathLibrary::RandomFloatInRange(0, 1), UKismetMathLibrary::RandomFloatInRange(0, 1));
		break;

	case ERandomColor::Selected:
		break;

	case ERandomColor::Altern:

		if (AlternativeColors.Num() > 0)
		{
			// Modulo of the number of Alternative Colors to alternate each colors
			Color = AlternativeColors[UKismetMathLibrary::Percent_ByteByte(uint8(NumInstance), uint8(AlternativeColors.Num()))];
		}
		break;

	default:
		break;
	}

	return;
}