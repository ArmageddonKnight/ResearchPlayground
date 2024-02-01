import * as https from "https";

import { SchemaRequestService } from "yaml-language-server/out/server/src/languageservice/yamlLanguageService";

export function createSchemaRequestHandler(): SchemaRequestService {
  return async (uri: string) => {
    console.log(`Schema used=${uri}`);
    return new Promise<string>((callback, error) => {
      const chunks: string[] = [];
      const request = https.get(uri, (res) => {
        res.setEncoding("utf8");

        res.on("data", (data: Buffer) => {
          chunks.push(data.toString());
        });

        res.on("end", () => {
          callback(chunks.join(""));
        });
      });

      request.on("error", (err) => error(err));
      request.end();
    });
  };
}
