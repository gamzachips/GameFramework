#include "../Common/pch.h"
#include "_08_Level.h"
#include "TestApp.h"
#include "../Common/World.h"
#include "../Common/Camera.h"
#include "../Common/Object.h"
#include "../Common/MeshRenderer.h"
#include "../Common/Material.h"
#include "../Common/Model.h"
#include "../Common/Animator.h"
#include "../Common/ResourceManager.h"
#include "../Common/Animation.h"
#include "../Common/Material.h"
#include "../Common/Environment.h"
#include "../Common/SkyboxCube.h"
#include "../Common/SkyboxRenderer.h"

_08_Level::_08_Level()
{
	std::srand(time(nullptr));
}

_08_Level::~_08_Level()
{
}

void _08_Level::Init(ComPtr<ID3D11Device> device)
{

	LightData lights;
	SetLightData(lights);

	_device = device;
	
	{
		std::string filePath = "../Resources/gun.fbx";
		TestApp::GetWorld()->GetResourceManager()->LoadFbx(filePath);

		_gun = new Object;
		AddObject(_gun);

		std::shared_ptr<Model> model = TestApp::GetWorld()->GetResourceManager()->GetOrCreateModel(_device);

		MeshRenderer* mr = new MeshRenderer(_device);
		mr->SetModel(model);

		std::shared_ptr<Environment> env = TestApp::GetWorld()->GetResourceManager()->GetOrCreateEnvironment(_device, "ruins");
		mr->SetEnvironment(env);

		_gun->AddComponent(mr);

		//_obj->GetTransform().SetSize({ 0.1f, 0.1f, 0.1f, 0.1f });
		_gun->GetTransform().SetSize({ 3.f, 3.f, 3.f, 3.f });
		_gun->GetTransform().Rotate(Vector4(0, 90, 0, 0));
		//_obj->GetTransform().SetPosition(Vector4(0, 0, 0, 0));
	}

	{
		std::string filePath = "../Resources/sphere.fbx";
		TestApp::GetWorld()->GetResourceManager()->LoadFbx(filePath);

		_sphere = new Object;
		AddObject(_sphere);

		std::shared_ptr<Model> model = TestApp::GetWorld()->GetResourceManager()->GetOrCreateModel(_device);

		MeshRenderer* mr = new MeshRenderer(_device);
		mr->SetModel(model);

		std::shared_ptr<Environment> env = TestApp::GetWorld()->GetResourceManager()->GetOrCreateEnvironment(_device, "ruins");
		mr->SetEnvironment(env);

		_sphere->AddComponent(mr);

	}

	{
		_skyboxObj = new Object;
		SkyboxRenderer* sr = new SkyboxRenderer(device);
		_skyboxObj->AddComponent(sr);
		sr->SetEnvironment(GameApp::GetWorld()->GetResourceManager()->GetOrCreateEnvironment(device, "ruins"));
		AddObject(_skyboxObj);
		_skyboxObj->GetTransform().SetSize(Vector4(1000.f, 1000.f, 1000.f, 1000.f));
	}

	__super::Init(device);

}

void _08_Level::Update(float deltaTime)
{
	__super::Update(deltaTime);
}

void _08_Level::Render(ComPtr<ID3D11DeviceContext> dc)
{
	__super::Render(dc);

	{ //ImGUI
		ImGui::Begin("Controls");


		ImGui::Text("Object:");
		static int selection = 0;

		ImGui::RadioButton("Sphere", selection == 0);
		if (ImGui::IsItemClicked())
			selection = 0;

		ImGui::SameLine();

		ImGui::RadioButton("Gun", selection == 1);
		if (ImGui::IsItemClicked())
			selection = 1;

		if (selection == 0)
		{
			_sphere->SetIsActive(true);
			_gun->SetIsActive(false);
		}
		else if (selection == 1)
		{
			_sphere->SetIsActive(false);
			_gun->SetIsActive(true);
		}


		ImGui::Text("Diffuse Map");
		ImGui::SameLine();
		ImGui::Checkbox("diffuse map", &hasDiffuse);

		ImGui::Text("Roughness Map");
		ImGui::SameLine();
		ImGui::Checkbox("roughness map", &hasRoughness);

		ImGui::Text("metalness Map");
		ImGui::SameLine();
		ImGui::Checkbox("metalness map", &hasMetalness);

		ImGui::Text("IBL");
		ImGui::SameLine();
		ImGui::Checkbox("IBL", &onIBL);

		if (!hasDiffuse)
		{
			ImGui::Text("Material: color");
			ImGui::SameLine();
			ImGui::SliderFloat3("rgb", &color.x, 0, 1);
		}

		if (!hasRoughness)
		{
			ImGui::Text("Material: roughness");
			ImGui::SameLine();
			ImGui::SliderFloat("roughness", &roughness, 0.1f, 1);
		}

		if (!hasMetalness)
		{
			ImGui::Text("Material: metalness");
			ImGui::SameLine();
			ImGui::SliderFloat("metalness", &metalness, 0, 1);
		}

	}


	std::vector<std::shared_ptr<Material>> gunMaterials = _gun->GetComponent<MeshRenderer>()->GetModel()->GetMaterials();
	std::vector<std::shared_ptr<Material>> sphereMaterials = _sphere->GetComponent<MeshRenderer>()->GetModel()->GetMaterials();

	for (auto& material : gunMaterials)
	{
		MaterialData& md = material->GetMaterialData();
		md.hasDiffuseMap = hasDiffuse;
		md.hasRoughnessMap = hasRoughness;
		md.hasMetalnessMap = hasMetalness;
		md.materialColor = color;
		md.roughness = roughness;
		md.metalness = metalness;
		md.onIBL = onIBL;
	}

	for (auto& material : sphereMaterials)
	{
		MaterialData& md = material->GetMaterialData();
		md.hasDiffuseMap = hasDiffuse;
		md.hasRoughnessMap = hasRoughness;
		md.hasMetalnessMap = hasMetalness;
		md.materialColor = color;
		md.roughness = roughness;
		md.metalness = metalness;
		md.onIBL = onIBL;
	}

	LightData& light = GetLightData();
	ImGui::Text("Light: radiance");
	ImGui::SliderFloat("r", &light.lightRadiance.x, 0, 1);
	ImGui::SliderFloat("g", &light.lightRadiance.y, 0, 1);
	ImGui::SliderFloat("b", &light.lightRadiance.z, 0, 1);
	
	ImGui::Text("Light: direction");
	ImGui::SliderFloat("x", &light.direction.x, -1, 1);
	ImGui::SliderFloat("y", &light.direction.y, -1, 1);
	ImGui::SliderFloat("z", &light.direction.z, -1, 1);


	ImGui::End();
}

