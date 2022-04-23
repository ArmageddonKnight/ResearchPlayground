# Analyzing Programming Puzzle Performance on Easily Accessible Models

## Summary

Driver by open-source models and accessible compute resources, this paper presents evaluate results of GPT-2 and GPT-Neo on P3, a dataset for solving Python Programming Puzzles.

## Quality [8/10]
  - Since this paper is trying to apply an existing, well understood solution to a new problem, the authors do not list any algorithms, equations, or theorems. My main concerns with the work are:
  
    - Not much insight into the performance of the models.

      After measuring the results on P3, the authors claim that the accuracy achieved by GPT-Neo is 20.6% whereas that achieved by GPT-2 is 10.9%. However, there is no explanation on what could potentially contribute to this accuracy difference. This, in my opinion, is particularly important if the authors want to motivate the readers to go for openly accessible and relatively small models, as we need to understand how and WHY these models fall short compared with the proprietary state-of-the-arts. 
      
      Similarly, in Figure 2, the authors also do not provide any reasoning on why medium could possibly outperform long in some cases (i.e., when the number of trials is 20 or 60). The lack of justification makes the claims in this paper weak and not convincing.

    - The paper's future works contradict its motivation.

      In the Abstract, the authors say that one of the main reasons for picking GPT-2 and GPT-Neo for their evaluations is to avoid "large proprietary models that demand substantial amounts of compute power", which makes sense and is definitely reasonable. However, in the Future Work/Limitations section, the authors claim that the main limitation of this work is that they do not have access to enough compute resources and larger and more complex models. However, this is contradictory to the motivation that has the authors pick GPT-2 and GPT-Neo in the first place.
  
    Based on the aforementioned weaknesses, I therefore give 8/10 on the quality of the paper and 7/10 on the originality and significance. Nevertheless, I personally do think that this is an exciting research direction and encourage the authors to move further.

## Clarity [10/10]
  - The paper is clearly written. However, I have the following advice:
    - The Abstract contains lots of technical details that could be moved to the Introduction section.
    - The Introduction section should be an extended version of the abstract (i.e., it should be self-contained). However, the current writing stops after stating the motivation of using GPT-2 and GPT-Neo.
    - The labels in Figure 1 could be increased for readability.

## Originality [7/10]
  - Please refer to the comments on 'Quality'.

## Significance [7/10]
  - Please refer to the comments on 'Quality'.

## Overall Merits [8/10]


# CNN Fine-tuned on Blurry Images Captures Blur Structure

## Summary

The paper studies how the CNNs derive the classification results and whether those results are affected by noisy images. By comparing between a naive classifier that is trained on clean images and an expert classifier that is trained on noisy images. The authors observe that the expert classifier tend to focus more on the object itself compared with the naive classifier and is also less affected by the noise.

## Quality [8/10]
  - The paper does not list any algorithms, equations, or theorems. However, the experiments are well formed and the methodology is clear. That being said, I have the following main concerns with the work:

    - No large-scale evaluations.

      The paper conducts preliminary experiments on two image classes: cats and dogs. However, to justify the impact of noisy images, the authors should include large-scale studies such as how noisy images could potentially affect the image classification accuracy on large datasets. Furthermore, I do not think that "the similarity of image categorization networks and human visual cortex" is persuasive enough as a motivation. As Professor Wang put it in class, modern neural networks are in fact quite different from human brains.

    - Out-of-date models.

      The paper uses AlexNet as the base model for naive and expert, which was published in 2012. As a model that is 10-years-old, AlexNet is quite out-dated now and is far from the state-of-the-art. The authors should consider replacing the base with a more recent network architecture such as ResNet, unless there is a strong reason for not doing so.

  Based on the aforementioned weaknesses, I therefore give 8/10 on the quality of the paper and 8/10 on the significance. Despite those weaknesses, I personally do think that this is an exciting research direction and encourage the authors to move further.

## Clarity [9/10]
  - The paper is clearly written. However, I think that both the Abstract and the Introduction section should include key conclusions so as to be self-contained. This can also help highlight your key contributions. However, with the current writeup the Abstract stops at methodology and the Introduction stops at problem statement.

## Originality [9/10]
  - This is a novel contribution to my best knowledge. 

## Significance [8/10]
  - Please refer to the comments on 'Quality'.

## Overall Merits [9/10]
