// customexport.js

tiled.registerMapFormat("MyMapFormat", {
    name: "Custom .map Format",
    extension: "map",

    write(map, fileName) {
        let file = new TextFile(fileName, TextFile.WriteOnly);
        file.write("|type|~id|x|y|\n");
        file.write(`SIZE ${map.width} ${map.height}\n`);

        const gravity = map.property("GRAVITY") || 512;
        file.write(`GRAVITY ${gravity}\n`);

        const friction = map.property("DEFAULT_FRICTION") || [0.8, 0];
        file.write(`DEFAULT_FRICTION ${friction[0]} ${friction[1]}\n`);

        const nextMap = map.property("NEXTMAP");
        if (nextMap) file.write(`NEXTMAP ${nextMap}\n`);

        map.layers.forEach(layer => {
            if (!layer.visible) return;

            if (layer.isTileLayer) {
                for (let y = 0; y < layer.height; ++y) {
                    for (let x = 0; x < layer.width; ++x) {
                        const tile = layer.tileAt(x, y);
                        if (tile) {
                            file.write(`TILE ${tile.id} ${x} ${y}\n`);
                        }
                    }
                }
            } else if (layer.isObjectLayer) {
                layer.objects.forEach(obj => {
                    const type = obj.type || obj.name || "UNKNOWN";
                    file.write(`${type} ${Math.floor(obj.x)} ${Math.floor(obj.y)}\n`);
                });
            }
        });

        file.commit();
        return true;
    }
});
