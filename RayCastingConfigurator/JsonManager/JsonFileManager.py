import json

from typing import Tuple
import os
import JsonManager.serialisation_classes as sclass

class RayCastingSettingsJsonFileManager:
    def __init__(self, title:str) -> None:
        if(os.path.exists(title)):
            self.title = title
        else: raise FileExistsError(title + " not exists")

    def to_json(self,window: sclass.Window, world: sclass.World, camera: sclass.Camera ):
        data = {"window": window.__dict__, "world": world.__dict__, "camera": camera.__dict__}
        with open(self.title, "w") as config:
            json.dump(data, config, indent=4)

    def from_json(self) -> Tuple[sclass.Window, sclass.World, sclass.Camera]:
        data = None
        with open(self.title, "r") as f:
            data = json.load(f)
        return sclass.Window(dictionary=data["window"]), sclass.World(dictionary=data["world"]), sclass.Camera(dictionary=data["camera"])

