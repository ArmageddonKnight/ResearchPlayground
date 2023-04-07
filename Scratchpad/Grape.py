    def process(self, input_ids, next_scores, next_tokens, next_indices):
        cur_len = input_ids.shape[-1]
        device = input_ids.device

        if cur_len == 2:
            import os
            os.environ["VERBOSE_CACHING_ALLOCATOR"] = "1"

        self.beam_scores = self.beam_scores.zero_().view(self.batch_size, self.group_size)
        next_beam_tokens = torch.zeros((self.batch_size, self.group_size), dtype=next_tokens.dtype, device=device)

        if cur_len == 2:
            os.environ["POINTER_TO_DEBUG"] = "1"

        next_beam_indices = torch.zeros((self.batch_size, self.group_size), dtype=next_indices.dtype, device=device)


        if cur_len == 2:
            os.environ["POINTER_TO_DEBUG"] = "0"

        batch_beam_indices = []

        for batch_idx, beam_hyp in enumerate(self.beam_hyps):
            batch_is_done = self.done[batch_idx]
            with G_GRAPE_GLOBAL_INDICATOR_STACK(batch_is_done):
                self.beam_scores[batch_idx, :] = 0
                next_beam_tokens[batch_idx, :] = self.pad_token_id
                next_beam_indices[batch_idx, :] = 0

            with G_GRAPE_GLOBAL_INDICATOR_STACK(batch_is_done.bitwise_not()):
                beam_idx = self._0.clone().detach()
                beam_idx_ne_group_size = self._true.clone().detach()
                for beam_token_rank, (next_token, next_score, next_index) in enumerate(
                    zip(next_tokens[batch_idx], next_scores[batch_idx], next_indices[batch_idx])
                ):
                    with G_GRAPE_GLOBAL_INDICATOR_STACK(beam_idx_ne_group_size):

                        if cur_len == 2 and beam_token_rank == 0:
                            os.environ["POINTER_TO_DEBUG"] = "2"
                            os.environ["POINTER_FREE_CHECKPOINT"] = "4"

                        if cur_len == 2 and beam_token_rank == 0:
                            os.environ["POINTER_TO_DEBUG"] = "3"
                            os.environ["POINTER_FREE_CHECKPOINT"] = "5"
                        batch_beam_idx = batch_idx * self._group_size + next_index

                        if cur_len == 2 and beam_token_rank == 0:
                            print(batch_beam_idx.dtype, next_beam_indices.dtype)
                            os.environ["POINTER_TO_DEBUG"] = "0"
                            os.environ["POINTER_FREE_CHECKPOINT"] = "1"



                        # batch_beam_idx = batch_beam_idx.clone().detach()
                        if cur_len == 2:
                            print("batch_beam_idx.data_ptr()={} @{}".format(hex(batch_beam_idx.data_ptr()), beam_token_rank))

                        if cur_len == 2 and beam_token_rank == 0:
                            os.environ["POINTER_FREE_CHECKPOINT"] = "2"

                        next_token_eq_eos = next_token == self.eos_token_id
                        if cur_len == 2 and beam_token_rank == 0:
                            os.environ["POINTER_FREE_CHECKPOINT"] = "102"
                        with G_GRAPE_GLOBAL_INDICATOR_STACK(next_token_eq_eos):
                            if cur_len == 2 and beam_token_rank == 0:
                                os.environ["POINTER_TO_DEBUG"] = "4"
                                os.environ["POINTER_FREE_CHECKPOINT"] = "103"
                            with G_GRAPE_GLOBAL_INDICATOR_STACK(self._group_size > self._beam_array[beam_token_rank]):
                                if cur_len == 2 and beam_token_rank == 0:
                                    os.environ["POINTER_FREE_CHECKPOINT"] = "104"
                                beam_hyp(
                                    input_ids[batch_beam_idx].clone().detach(),
                                    next_score,
                                )
                            if cur_len == 2 and beam_token_rank == 0:
                                os.environ["POINTER_TO_DEBUG"] = "0"

                        # SomeVariableThasHasNeverBeenNamed = 
                        # if cur_len == 2 and beam_token_rank == 0:
                        #     print(A.data_ptr())
                        with G_GRAPE_GLOBAL_INDICATOR_STACK(next_token_eq_eos.bitwise_not()):
                        # if True:
                            self.beam_scores[batch_idx, beam_idx] = next_score
                            next_beam_tokens[batch_idx, beam_idx] = next_token
                            next_beam_indices[batch_idx, beam_idx] = batch_beam_idx
                            beam_idx += self._1

                        beam_idx_ne_group_size = beam_idx != self._group_size

                        if cur_len == 2:
                            print("next_beam_indices.data_ptr()={} @{}".format(hex(next_beam_indices.data_ptr()), beam_token_rank))

                        # batch_beam_indices.append(batch_beam_idx)

            self.done[batch_idx].bitwise_or_(beam_hyp.is_done(next_scores[batch_idx].max(), cur_len))
        
        if cur_len == 2:
            import os
            os.environ["VERBOSE_CACHING_ALLOCATOR"] = "0"
        self.beam_scores = self.beam_scores.view(-1)
        return next_beam_tokens.view(-1), next_beam_indices.view(-1)


            print(
                f"ckpt #0 cur_len={cur_len}, outputs.past_key_values[1][0]={outputs.past_key_values[0][0][0, 0, :, :]}"
            )
            print(
                f"ckpt #0 cur_len={cur_len}, outputs.past_key_values[1][0]={outputs.past_key_values[1][0][0, 0, :, :]}"
            )
            print(
                f"ckpt #0 cur_len={cur_len}, outputs.past_key_values[1][0].data_ptr()={hex(outputs.past_key_values[1][0].data_ptr())}"
            )
            torch._C._lookupDataPtrInMemtape(
                torch.cuda.current_device(),
                graphed_beam_search_post_processor.mempool_id,
                outputs.past_key_values[1][0].data_ptr(),
            )

            if cur_len == 1:
                print("Checkpointing past_key_values")
                print(outputs.past_key_values[0][0])
                for past_idx, past_kv in enumerate(outputs.past_key_values):
                    for vi, v in enumerate(past_kv):
                        torch.save(v, f"past_key_value-{past_idx}-{vi}.pt")


            if cur_len == 1:
                print("Verifying past_key_values")
                print(new_input_ids)
                torch._C._lookupDataPtrInMemtape(
                    torch.cuda.current_device(),
                    graphed_beam_search_post_processor.mempool_id,
                    new_input_ids.data_ptr()
                )
                print(f"new_input_ids.data_ptr()={hex(new_input_ids.data_ptr())}")
                for past_idx, past_kv in enumerate(outputs.past_key_values):
                    for vi, v in enumerate(past_kv):
                        loaded = torch.load(f"past_key_value-{past_idx}-{vi}.pt")
                        if not torch.allclose(v, loaded):
                            print(f"{past_idx}, {vi}, v.data_ptr()={hex(v.data_ptr())} has changed")
                            print(f"loaded.data_ptr()={hex(loaded.data_ptr())}-{hex(loaded.data_ptr() + loaded.nelement() * loaded.element_size())}")
                            v = loaded

            print(
                f"ckpt #2 cur_len={cur_len}, outputs.past_key_values[1][0]={outputs.past_key_values[0][0][0, 0, :, :]}"
            )
            print(
                f"ckpt #2 cur_len={cur_len}, outputs.past_key_values[1][0]={outputs.past_key_values[1][0][0, 0, :, :]}"
            )
            print(
                f"ckpt #2 cur_len={cur_len}, outputs.past_key_values[1][0].data_ptr()={hex(outputs.past_key_values[1][0].data_ptr())}"
            )

            print("After entering: ", input_ids, negative(outputs.logits))


        # # self.worst_score[0] = self._3f
        # # with G_GRAPE_GLOBAL_INDICATOR_STACK((self.len < self._num_beams).bitwise_or(score > self.worst_score)):
        # #     self.worst_score[0] = self._2f
        # #     self.scoreboard[0] = self._3f

        # with G_GRAPE_GLOBAL_INDICATOR_STACK((self.len < self._num_beams)):
        #     # with G_GRAPE_GLOBAL_INDICATOR_STACK(self._true):
        #     self.worst_score[0] = self._1f

        # score = sum_logprobs / (hyp.shape[-1] ** self.length_penalty)

        # # self.score_copy[0] = score

        # # with G_GRAPE_GLOBAL_INDICATOR_STACK(self._true):
        # with G_GRAPE_GLOBAL_INDICATOR_STACK((self.len < self._num_beams)):
        #     # score = sum_logprobs / (hyp.shape[-1] ** self.length_penalty)
        #     self.score_copy[0] = self._3f
        #     # self.worst_score[0] = score

        # with G_GRAPE_GLOBAL_INDICATOR_STACK((self.len > self._num_beams)):
        #     # score = sum_logprobs / (hyp.shape[-1] ** self.length_penalty)
        #     self.score_copy[1] = self._2f

        # with G_GRAPE_GLOBAL_INDICATOR_STACK((self.len < self._num_beams)):
        #     # score = sum_logprobs / (hyp.shape[-1] ** self.length_penalty)
        #     self.score_copy[0] = self._3f

        # with G_GRAPE_GLOBAL_INDICATOR_STACK((self.len < self._num_beams).bitwise_or(score > self.worst_score)):

        #     self.score_copy[0] = self.score_copy[0] + self._1f

        #     # self.len += self._1
        #     len_gt_num_beams_add_one = self.len > (self._num_beams + self._1)
        #     with G_GRAPE_GLOBAL_INDICATOR_STACK(len_gt_num_beams_add_one):
        #         self.scoreboard[0] = score

        #     #     self.scoreboard_items[0, : hyp.shape[-1]] = hyp
        #     # with G_GRAPE_GLOBAL_INDICATOR_STACK(len_gt_num_beams_add_one.bitwise_not()):
        #     #     self.scoreboard[-1] = score
        #     #     self.scoreboard_items[-1, : hyp.shape[-1]] = hyp
        #     # scoreboard_sort_res = torch.sort(self.scoreboard)
        #     # self.scoreboard[:] = scoreboard_sort_res.values
        #     # self.scoreboard_items[:, :] = torch.index_select(
        #     #     self.scoreboard_items, dim=0, index=scoreboard_sort_res.indices
        #     # )
        #     len_gt_num_beams = self.len > self._num_beams
        #     with G_GRAPE_GLOBAL_INDICATOR_STACK(len_gt_num_beams):
        #         self.worst_score[0] = self._1f
        #     with G_GRAPE_GLOBAL_INDICATOR_STACK(len_gt_num_beams.bitwise_not()):
        #         self.worst_score[0] = self._1f # torch.min(self.worst_score[0], score)
        #     self.worst_score[0] = self._3f
        # # with G_GRAPE_GLOBAL_INDICATOR_STACK((self.len < self._num_beams).bitwise_or(score > self.worst_score)):
        # #     self.worst_score[0] = self._2f
        # #     self.scoreboard[0] = self._3f


        