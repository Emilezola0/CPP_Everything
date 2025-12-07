// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_CubeFrame.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
ACPP_CubeFrame::ACPP_CubeFrame()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Scene Root using Scene Component
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRootComponent"));

	// Add Text Render AND attach it to SceneRoot
	BpName = CreateDefaultSubobject<UTextRenderComponent>(TEXT("NAME OF THE BP"));
	BpName->SetupAttachment(SceneRoot);

	CubeCount = CreateDefaultSubobject<UTextRenderComponent>(TEXT("NumberOfCubes"));
	CubeCount->SetupAttachment(SceneRoot);

	// HISM
	HISM_00 = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("HISM_00"));
	HISM_00->SetupAttachment(SceneRoot);

	// Setup Variables Default Value(s) (If needed)
	StoneZ_Offset = 50.f;
	bRenderText = false;
	MeshColor = { 1.0f, 1.0f, 1.0f, 1.0f };

}

void ACPP_CubeFrame::OnConstruction(const FTransform& Transform)
{
	// Clear Instances
	HISM_00->ClearInstances();

	if (SM_Stone && Stones_X > 0 && Stones_Y > 0 && Stones_Z > 0 && Material) 
	{
		// Set Static mesh to SM_Stone
		HISM_00->SetStaticMesh(SM_Stone);
		// HISM COLORS
		HISM_00->NumCustomDataFloats = 3;
		// SET THE MATERIAL to the HISM
		HISM_00->SetMaterial(0, Material);

		// DECLARE L_COLOR
		FLinearColor L_Color = { 1.0f, 1.0f, 1.0f, 1.0f };

		// Setup for loop
		int i = 0;
		// For (Fist Index = 0) to Last Index (i < Variable) then add 1 to i
		for (i = 0; i < Stones_X; i++)
		{
			int j = 0;
			for (j = 0; j < Stones_Y; j++) 
			{
				int k = 0;
				for (k = 0; k < Stones_Z; k++)
				{
					int AxeX = i;
					int AxeY = j;
					int AxeZ = k;
					if (
						CubeFrameCondition(AxeY, Stones_Y) && CubeFrameCondition(AxeZ, Stones_Z) ||
						CubeFrameCondition(AxeX, Stones_X) && CubeFrameCondition(AxeY, Stones_Y) ||
						CubeFrameCondition(AxeX, Stones_X) && CubeFrameCondition(AxeZ, Stones_Z)
						)
					{
						// Setup Vector Location with Mesh Size * Each Index for a 3D Directionnal Instance
						FVector L_FinalLoc = (GetMeshHalfSize() * FVector(2.f, 2.f, 2.f)) * FVector(AxeX, AxeY, AxeZ);
						
						// Add Z Offset
						L_FinalLoc += FVector(0.f, 0.f, StoneZ_Offset);

						// Variable Transform of the future HISM
						FTransform L_InstanceTransform = FTransform(
							FRotator::ZeroRotator,
							FVector(L_FinalLoc),
							FVector(1.f, 1.f, 1.f)
						);
						// SET TO HAVE INSTANCE INDEX
						int L_CurrentInstanceIndex = HISM_00->AddInstance(L_InstanceTransform);

						// CHECK IF HAVE A MATERIAL
						switch (RandomGenerationType)
						{
						case ETypeOfRnd::None:
							// DO NOTHING
							// SET CUSTOM DATA VALUE FOR R, G, B
							HISM_00->SetCustomDataValue(L_CurrentInstanceIndex, 0, 1.f, false);
							HISM_00->SetCustomDataValue(L_CurrentInstanceIndex, 1, 1.f, false);
							HISM_00->SetCustomDataValue(L_CurrentInstanceIndex, 2, 1.f, false);
							break;

						case ETypeOfRnd::Random:
							// Random Color (not seeded)
							UKismetMathLibrary::LinearColor_SetRandomHue(L_Color);

							// SET CUSTOM DATA VALUE FOR R, G, B
							HISM_00->SetCustomDataValue(L_CurrentInstanceIndex, 0, L_Color.R, false);
							HISM_00->SetCustomDataValue(L_CurrentInstanceIndex, 1, L_Color.G, false);
							HISM_00->SetCustomDataValue(L_CurrentInstanceIndex, 2, L_Color.B, false);
							
							break;

						case ETypeOfRnd::Seeded:
							// MAKE A SEEDED
							// SET CUSTOM DATA VALUE FOR R, G, B
							HISM_00->SetCustomDataValue(L_CurrentInstanceIndex, 0, 1.f, false);
							HISM_00->SetCustomDataValue(L_CurrentInstanceIndex, 1, 1.f, false);
							HISM_00->SetCustomDataValue(L_CurrentInstanceIndex, 2, 1.f, false);
							break;
						
						case ETypeOfRnd::Selected:
							// SET CUSTOM DATA VALUE FOR R, G, B  ->  From Selected
							HISM_00->SetCustomDataValue(L_CurrentInstanceIndex, 0, MeshColor.R, false);
							HISM_00->SetCustomDataValue(L_CurrentInstanceIndex, 1, MeshColor.G, false);
							HISM_00->SetCustomDataValue(L_CurrentInstanceIndex, 2, MeshColor.B, false);
							break;

						default:
							// Always put a default
							// SET CUSTOM DATA VALUE FOR R, G, B
							HISM_00->SetCustomDataValue(L_CurrentInstanceIndex, 0, 1.f, false);
							HISM_00->SetCustomDataValue(L_CurrentInstanceIndex, 1, 1.f, false);
							HISM_00->SetCustomDataValue(L_CurrentInstanceIndex, 2, 1.f, false);
							break;
						}
					}
				}
			}
		}
	}
	// --------------------------
	// TEXTS
	// --------------------------

	// BP NAME TEXT
	BpName->SetText(FText::FromString("BP_CubeFrame"));
	// PLACEMENT
	BpName->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	BpName->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
	BpName->SetRelativeLocation(FVector((float(Stones_X) - 1) * GetMeshHalfSize().X, (float(Stones_Y) - 1) * GetMeshHalfSize().Y, (float(Stones_Z) - 1) * GetMeshHalfSize().Z + 25.f));

	// NUMBER OF INSTANCE TEXT
	FString L_CubeCount = "CubeCount : ";
	L_CubeCount.AppendInt(HISM_00->GetInstanceCount());
	CubeCount->SetText(FText::FromString(L_CubeCount));
	// PLACEMENT
	CubeCount->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	CubeCount->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
	CubeCount->SetRelativeLocation(FVector((float(Stones_X) - 1) * GetMeshHalfSize().X, (float(Stones_Y) - 1) * GetMeshHalfSize().Y, (float(Stones_Z) - 1)* GetMeshHalfSize().Z - 25.f));

}

// Called when the game starts or when spawned
void ACPP_CubeFrame::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_CubeFrame::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ACPP_CubeFrame::CubeFrameCondition(int Index, int Stone) 
{
	return (Index == 0 || Stone - 1 == Index);
}

FVector ACPP_CubeFrame::GetMeshHalfSize()
{
	return SM_Stone->GetBounds().GetBox().GetExtent();
}

