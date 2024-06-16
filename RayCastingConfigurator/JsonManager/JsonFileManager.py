import json

import RayCastingConfigurator.JsonManager.serialisation_classes as sclass

class RayCastingSettingsJsonFileManager:
    def __init__(self, title:str) -> None:
        self.title = title

    def to_json(self,window: sclass.Window, world: sclass.World, camera: sclass.Camera ):
        data = {"window": window.__dict__, "world": world.__dict__, "camera": camera.__dict__}
        with open(self.title, "w") as config:
            json.dump(data, config, indent=4)

    def from_json(self) -> tuple[sclass.Window, sclass.World, sclass.Camera]:
        data = None
        with open(self.title, "r") as f:
            data = json.load(f)
        print(data)
        return sclass.Window(data["window"]), sclass.World(data["world"]), sclass.Camera(data["camera"])

