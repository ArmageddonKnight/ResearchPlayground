#!/usr/bin/env node

import { validateWithSchema } from "./validate";
import { program } from "commander";

async function main() {
  program
    .command("schema")
    .description("Validate YAML files against the given schema path or URL.")
    .argument("<schema>", "The schema to use for validation")
    .argument(
      "<patterns...>",
      "The glob patterns for YAML files to be validated",
    )
    .option("--yamlVersion", "The YAML version to use for validation")
    .action(async (schema, patterns, options) => {
      const error = await validateWithSchema(
        { yamlVersion: options.yamlVersion },
        schema,
        patterns,
      );
      if (error !== undefined) {
        process.exit(1);
      }
    });
  program.parse(process.argv);
}

(async function () {
  await main();
})();
