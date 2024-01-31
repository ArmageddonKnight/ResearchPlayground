#!/usr/bin/env node

import { program } from "commander";

async function main() {
  program
    .command("schema")
    .argument("<schema>", "The schema to use for validation")
    .argument(
      "<patterns...>",
      "The glob patterns for YAML files to be validated",
    )
    .option("--yaml-version", "The YAML version to use for validation")
    .description("Validate YAML files against the given schema path or URI.")
    .action(async (schema, files, options) => {});
}

(async function () {
  await main();
})();
