// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_CrossDiagonal.h"

// Sets default values
ACPP_CrossDiagonal::ACPP_CrossDiagonal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup Components
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));

	HISM_00 = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("HISM_00"));
	HISM_00->SetupAttachment(SceneRoot);

	BpName = CreateDefaultSubobject<UTextRenderComponent>(TEXT("BpName"));
	BpName->SetupAttachment(SceneRoot);

	CubeCount = CreateDefaultSubobject<UTextRenderComponent>(TEXT("CubeCount"));
	CubeCount->SetupAttachment(SceneRoot);

	// Setup Variables

}

void ACPP_CrossDiagonal::OnConstruction(const FTransform& Transform)
{
	// HISM
	HISM_00->ClearInstances();

	// SOME VARIABLES TO DECLARE
	int L_CurrentMin;
	int L_CurrentMax;

	FVector L_Location;

	if (SM_Stone && Stones_XY > 0)
	{
		// SET STATIC MESH
		HISM_00->SetStaticMesh(SM_Stone);

		// FOR LOOP
		int i = 0.f;
		int j = 0.f;
		for (i = 0; i < Stones_XY; i++)
		{
			for (j = 0; j < Stones_XY; j++)
			{
				L_CurrentMin = i;
				L_CurrentMax = (Stones_XY - 1) - i;

				// Validate a condition to instantiate
				if (L_CurrentMin == j || L_CurrentMax == j)
				{
					// MAKE LOCATION
					L_Location = FVector(
						// Axe X
						GetMeshHalfSize().X * 2 * i, 
						// Axe Y
						0.f, 
						// Axe Z
						GetMeshHalfSize().Z * 2 * j);


					// ADD INSTANCE
					HISM_00->AddInstance(FTransform(
						FRotator::ZeroRotator,
						L_Location,
						FVector(1.f, 1.f, 1.f)
					)
					);
				}
			}
		}
		// END FOR LOOP

		// ---------------------
		// TEXTs

		// Name
		BpName->SetText(FText::FromString("Cross Diagonal"));
		// Cube Count
		FString L_TextCubeCount = "Cube Count : ";
		L_TextCubeCount.AppendInt(HISM_00->GetInstanceCount());
		CubeCount->SetText(FText::FromString(L_TextCubeCount));

		// PLACEMENT
		BpName->SetRelativeLocation(FVector(GetMeshHalfSize().X * (Stones_XY - 1), GetMeshHalfSize().Y + 10.f, (GetMeshHalfSize().Z * (Stones_XY - 1)) + 25));
		CubeCount->SetRelativeLocation(FVector(GetMeshHalfSize().X * (Stones_XY - 1), GetMeshHalfSize().Y + 10.f, (GetMeshHalfSize().Z * (Stones_XY - 1)) - 25));

		// PITCH, YAW, ROLL
		BpName->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));
		CubeCount->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));

		// ALIGNEMENT
		BpName->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
		CubeCount->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
		BpName->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
		CubeCount->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
	}


}

// Called when the game starts or when spawned
void ACPP_CrossDiagonal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_CrossDiagonal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ACPP_CrossDiagonal::GetMeshHalfSize()
{
	return SM_Stone->GetBounds().GetBox().GetExtent();
}