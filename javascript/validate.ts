import { glob } from 'glob';
import { YamlVersion } from 'yaml-language-server/out/server/src/languageservice/parser/yamlParser07';

export interface Settings {
  yamlVersion?: YamlVersion;
}

export async function validateWithSchema(
  settings: Settings,
  schema: string,
  ...patterns: string[]
) {
  console.log('Searching YAML files with patterns=', patterns);
  const files = await Promise.all(
    patterns.map(
      (pattern) =>
        new Promise<string[]>((callback, error) => {
          glob(pattern, { nodir: true });
        }),
    ),
  ).then((filesArrays) => filesArrays.flat());
  console.log('Validating YAML files=', files);
}
