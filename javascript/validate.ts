import { YAMLSchemaService } from "yaml-language-server/out/server/src/languageservice/services/yamlSchemaService";
import { YAMLValidation } from "yaml-language-server/out/server/src/languageservice/services/yamlValidation";
import { YamlVersion } from "yaml-language-server/out/server/src/languageservice/parser/yamlParser07";
import { Diagnostic } from "vscode-languageserver-types";

export interface ValidationOptions {
  yamlVersion?: YamlVersion;
  schema: string;
}

interface FileValidationResult {
  filePath: string;
  diagnostic: Diagnostic[];
}

async function _validate(
  files: string[],
  options: ValidationOptions,
): Promise<FileValidationResult[]> {
  
}

async function _validateAndOutput(files: string[], options: ValidationOptions) {
  console.log(`Validating ${files.length} YAML files.`);
  const validation_errors = await _validate(files, options);

  if (validation_errors.length == 0) {
    console.log("All done. No errors found.");
    return;
  }

  console.error("Found invalid files:");
  for (const validation_error of validation_errors) {
    for (const error of validation_error.diagnostic) {
      console.error(
        `${error.filePath}:${error.range.start.line + 1}:${error.range.start.character + 1}: ${error.message}`,
      );
    }
  }

  return validation_errors;
}

export async function validateWithSchema(
  options: ValidationOptions,
  files: string[],
) {
  console.log("Validating YAML files=", files);
  return _validateAndOutput(files, options);
}
