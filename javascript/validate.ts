import * as fs from "fs";
import * as path from "path";

import { Diagnostic } from "vscode-languageserver-types";
import { TelemetryEvent } from "yaml-language-server/out/server/src/languageservice/telemetry";
import { TextDocument } from "vscode-languageserver-textdocument";
import { WorkspaceContextService } from "yaml-language-server/out/server/src/languageservice/yamlLanguageService";
import { YAMLSchemaService } from "yaml-language-server/out/server/src/languageservice/services/yamlSchemaService";
import { YAMLValidation } from "yaml-language-server/out/server/src/languageservice/services/yamlValidation";
import { YamlVersion } from "yaml-language-server/out/server/src/languageservice/parser/yamlParser07";

import { createSchemaRequestHandler } from "./schema";

interface _ValidationOptions {
  yamlVersion?: YamlVersion;
  schema: string;
}

class _ConsoleTelemetry {
  constructor() {}

  send(event: TelemetryEvent): void {
    console.error("send:", event);
  }
  sendError(name: string, properties: unknown): void {
    console.error("sendError:", name, properties);
  }
  sendTrack(name: string, properties: unknown): void {
    console.error("sendTrack:", name, properties);
  }
}

interface _FileValidationResult {
  filePath: string;
  diagnostic: Diagnostic[];
}

async function _validate(
  files: string[],
  validationOptions: _ValidationOptions,
): Promise<_FileValidationResult[]> {
  const workspaceContext: WorkspaceContextService = {
    resolveRelativePath: (relativePath: string, resource: string) => {
      return path.join(path.dirname(resource), relativePath);
    },
  };
  const schemaService = new YAMLSchemaService(
    createSchemaRequestHandler(),
    workspaceContext,
  );

  schemaService.addSchemaPriority(validationOptions.schema, 0);
  schemaService.registerExternalSchema(validationOptions.schema, ["*"]);

  const yamlValidation = new YAMLValidation(
    schemaService,
    new _ConsoleTelemetry(),
  );
  yamlValidation.configure({
    validate: true,
    yamlVersion: validationOptions?.yamlVersion ?? "1.2",
    disableAdditionalProperties: false,
    customTags: [],
  });

  return await Promise.all(
    files.map(async (filePath: string) => {
      const doc = TextDocument.create(
        filePath,
        "yaml",
        0,
        fs.readFileSync(filePath).toString(),
      );

      return await yamlValidation
        .doValidation(doc)
        .then((diagnostic) => ({ filePath, diagnostic }));
    }),
  ).then((rets) => rets.filter((ret) => ret.diagnostic.length > 0));
}

async function _validateAndOutput(
  files: string[],
  validationOptions: _ValidationOptions,
) {
  console.log(`Validating ${files.length} YAML files.`);
  const validation_errors = await _validate(files, validationOptions);

  if (validation_errors.length == 0) {
    console.log("All done. No errors found.");
    return;
  }

  console.error("Found invalid files:");
  for (const validation_error of validation_errors) {
    for (const error of validation_error.diagnostic) {
      console.error(
        `${error.code}:${error.range.start.line + 1}:${error.range.start.character + 1}: ${error.message}`,
      );
    }
  }

  return validation_errors;
}

export async function validateWithSchema(
  options: _ValidationOptions,
  files: string[],
) {
  console.log(`Validating YAML files=${files}`);
  return _validateAndOutput(files, options);
}
